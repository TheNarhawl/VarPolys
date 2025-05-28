#include "AVLTreePolynom.h"
#include <cmath>
#include <algorithm>

AVLTreePolynom::Term::Term(double coeff, const std::map<char, int>& vars)
    : coefficient(coeff), variables(vars) {
}

bool AVLTreePolynom::Term::operator<(const Term& other) const {
    int this_degree = 0, other_degree = 0;
    for (const auto& [var, exp] : variables) this_degree += exp;
    for (const auto& [var, exp] : other.variables) other_degree += exp;

    if (this_degree != other_degree) return this_degree > other_degree;

    auto it1 = variables.begin(), it2 = other.variables.begin();
    while (it1 != variables.end() && it2 != other.variables.end()) {
        if (it1->first != it2->first) return it1->first < it2->first;
        if (it1->second != it2->second) return it1->second > it2->second;
        ++it1; ++it2;
    }
    return variables.size() > other.variables.size();
}

bool AVLTreePolynom::Term::operator==(const Term& other) const {
    return variables == other.variables;
}

AVLTreePolynom::AVLNode::AVLNode(const Term& t)
    : term(t), left(nullptr), right(nullptr), height(1) {
}

AVLTreePolynom::AVLTreePolynom() : root(nullptr), size(0) {}

AVLTreePolynom::AVLTreePolynom(const AVLTreePolynom& other)
    : root(copyTree(other.root)), size(other.size) {
}

AVLTreePolynom::AVLTreePolynom(AVLTreePolynom&& other) noexcept
    : root(other.root), size(other.size) {
    other.root = nullptr;
    other.size = 0;
}

AVLTreePolynom& AVLTreePolynom::operator=(const AVLTreePolynom& other) {
    if (this != &other) {
        clear(root);
        root = copyTree(other.root);
        size = other.size;
    }
    return *this;
}

AVLTreePolynom& AVLTreePolynom::operator=(AVLTreePolynom&& other) noexcept {
    if (this != &other) {
        clear(root);
        root = other.root;
        size = other.size;
        other.root = nullptr;
        other.size = 0;
    }
    return *this;
}

AVLTreePolynom::~AVLTreePolynom() {
    clear(root);
}

int AVLTreePolynom::height(AVLNode* node) const {
    return node ? node->height : 0;
}

int AVLTreePolynom::balanceFactor(AVLNode* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

void AVLTreePolynom::updateHeight(AVLNode* node) {
    if (node)
        node->height = 1 + std::max(height(node->left), height(node->right));
}

AVLTreePolynom::AVLNode* AVLTreePolynom::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

AVLTreePolynom::AVLNode* AVLTreePolynom::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLTreePolynom::AVLNode* AVLTreePolynom::balance(AVLNode* node) {
    if (!node) return nullptr;
    updateHeight(node);
    int bf = balanceFactor(node);
    if (bf > 1) {
        if (balanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (bf < -1) {
        if (balanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

AVLTreePolynom::AVLNode* AVLTreePolynom::insert(AVLNode* node, const Term& term) {
    if (!node) {
        size++;
        return new AVLNode(term);
    }
    if (term == node->term) {
        node->term.coefficient += term.coefficient;
        if (node->term.coefficient == 0)
            return remove(node, term);
        return node;
    }
    if (term < node->term)
        node->left = insert(node->left, term);
    else
        node->right = insert(node->right, term);
    return balance(node);
}

AVLTreePolynom::AVLNode* AVLTreePolynom::findMin(AVLNode* node) const {
    while (node && node->left)
        node = node->left;
    return node;
}

AVLTreePolynom::AVLNode* AVLTreePolynom::remove(AVLNode* node, const Term& term) {
    if (!node) return nullptr;
    if (term < node->term)
        node->left = remove(node->left, term);
    else if (node->term < term)
        node->right = remove(node->right, term);
    else {
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp;
            }
            delete temp;
            size--;
        }
        else {
            AVLNode* temp = findMin(node->right);
            node->term = temp->term;
            node->right = remove(node->right, temp->term);
        }
    }
    return balance(node);
}

void AVLTreePolynom::inOrderTraversal(AVLNode* node, std::vector<Term>& terms) const {
    if (!node) return;
    inOrderTraversal(node->left, terms);
    terms.push_back(node->term);
    inOrderTraversal(node->right, terms);
}

void AVLTreePolynom::clear(AVLNode* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

AVLTreePolynom::AVLNode* AVLTreePolynom::copyTree(AVLNode* node) const {
    if (!node) return nullptr;
    AVLNode* newNode = new AVLNode(node->term);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    newNode->height = node->height;
    return newNode;
}

void AVLTreePolynom::addTerm(double coefficient, const std::map<char, int>& variables) {
    if (coefficient == 0) return;
    Term term(coefficient, variables);
    root = insert(root, term);
}

AVLTreePolynom AVLTreePolynom::operator+(const AVLTreePolynom& other) const {
    AVLTreePolynom result = *this;
    std::vector<Term> otherTerms;
    other.inOrderTraversal(other.root, otherTerms);
    for (const auto& term : otherTerms)
        result.addTerm(term.coefficient, term.variables);
    return result;
}

AVLTreePolynom AVLTreePolynom::operator-(const AVLTreePolynom& other) const {
    AVLTreePolynom result = *this;
    std::vector<Term> otherTerms;
    other.inOrderTraversal(other.root, otherTerms);
    for (const auto& term : otherTerms)
        result.addTerm(-term.coefficient, term.variables);
    return result;
}

AVLTreePolynom AVLTreePolynom::operator*(const AVLTreePolynom& other) const {
    AVLTreePolynom result;
    std::vector<Term> thisTerms, otherTerms;
    this->inOrderTraversal(root, thisTerms);
    other.inOrderTraversal(other.root, otherTerms);
    for (const auto& a : thisTerms) {
        for (const auto& b : otherTerms) {
            std::map<char, int> newVars = a.variables;
            for (const auto& [var, exp] : b.variables)
                newVars[var] += exp;
            result.addTerm(a.coefficient * b.coefficient, newVars);
        }
    }
    return result;
}

void AVLTreePolynom::print() const {
    std::vector<Term> terms;
    inOrderTraversal(root, terms);
    bool isFirstTerm = true;
    bool hasTerms = false;
    for (const auto& term : terms) {
        if (term.coefficient == 0) continue;
        hasTerms = true;
        if (!isFirstTerm) {
            std::cout << (term.coefficient >= 0 ? " + " : " - ");
        }
        else {
            if (term.coefficient < 0) std::cout << "-";
        }
        double absCoeff = std::abs(term.coefficient);
        if (absCoeff != 1.0 || term.variables.empty())
            std::cout << absCoeff;
        for (const auto& [var, exp] : term.variables) {
            std::cout << var;
            if (exp != 1)
                std::cout << "^" << exp;
        }
        isFirstTerm = false;
    }
    if (!hasTerms) std::cout << "0";
    std::cout << std::endl;
}

void AVLTreePolynom::clear() {
    clear(root);
    root = nullptr;
    size = 0;
}

size_t AVLTreePolynom::getSize() const {
    return size;
}

std::vector<AVLTreePolynom::Term> AVLTreePolynom::getTerms() const {
    std::vector<Term> terms;
    inOrderTraversal(root, terms);
    return terms;
}

