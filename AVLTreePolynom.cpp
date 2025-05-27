#include "AVLTreePolynom.h"

bool Monomial::operator<(const Monomial& other) const {
    return variables < other.variables;
}

bool Monomial::operator==(const Monomial& other) const {
    return variables == other.variables;
}

std::string Monomial::toString() const {
    std::ostringstream oss;
    oss << (coefficient >= 0 ? "+" : "") << coefficient;
    for (const auto& [var, exp] : variables) {
        oss << var;
        if (exp != 1) oss << "^" << exp;
    }
    return oss.str();
}

Node::Node(const Monomial& m) : monom(m), left(nullptr), right(nullptr), height(1) {}

AVLTreePolynom::AVLTreePolynom() : root(nullptr) {}
AVLTreePolynom::~AVLTreePolynom() { destroy(root); }

void AVLTreePolynom::destroy(Node* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

int AVLTreePolynom::height(Node* n) {
    return n ? n->height : 0;
}

int AVLTreePolynom::getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* AVLTreePolynom::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* AVLTreePolynom::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    return y;
}

Node* AVLTreePolynom::insert(Node* node, const Monomial& m) {
    if (!node) return new Node(m);
    if (m < node->monom) node->left = insert(node->left, m);
    else if (node->monom < m) node->right = insert(node->right, m);
    else {
        node->monom.coefficient += m.coefficient;
        return node;
    }

    node->height = std::max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);

    if (balance > 1 && m < node->left->monom) return rotateRight(node);
    if (balance < -1 && node->right->monom < m) return rotateLeft(node);
    if (balance > 1 && node->left->monom < m) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && m < node->right->monom) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

void AVLTreePolynom::insert(const Monomial& m) {
    if (m.coefficient != 0.0)
        root = insert(root, m);
}

void AVLTreePolynom::inorder(Node* node) const {
    if (!node) return;
    inorder(node->left);
    std::cout << node->monom.toString() << " ";
    inorder(node->right);
}

void AVLTreePolynom::print() const {
    inorder(root);
    std::cout << std::endl;
}

void AVLTreePolynom::traverseAndInsert(Node* node, AVLTreePolynom& target, double sign) const {
    if (!node) return;
    traverseAndInsert(node->left, target, sign);
    Monomial m = node->monom;
    m.coefficient *= sign;
    target.insert(m);
    traverseAndInsert(node->right, target, sign);
}

AVLTreePolynom AVLTreePolynom::operator+(const AVLTreePolynom& other) const {
    AVLTreePolynom result;
    traverseAndInsert(this->root, result, 1);
    traverseAndInsert(other.root, result, 1);
    return result;
}

AVLTreePolynom AVLTreePolynom::operator-(const AVLTreePolynom& other) const {
    AVLTreePolynom result;
    traverseAndInsert(this->root, result, 1);
    traverseAndInsert(other.root, result, -1);
    return result;
}

void AVLTreePolynom::multiplyWith(Node* a, const AVLTreePolynom& other, AVLTreePolynom& result) const {
    if (!a) return;
    multiplyWith(a->left, other, result);
    multiplyByMonomial(other.root, a->monom, result);
    multiplyWith(a->right, other, result);
}

void AVLTreePolynom::multiplyByMonomial(Node* b, const Monomial& m, AVLTreePolynom& result) const {
    if (!b) return;
    multiplyByMonomial(b->left, m, result);

    Monomial newMonom;
    newMonom.coefficient = b->monom.coefficient * m.coefficient;
    newMonom.variables = b->monom.variables;

    for (const auto& [var, exp] : m.variables) {
        newMonom.variables[var] += exp;
    }

    result.insert(newMonom);
    multiplyByMonomial(b->right, m, result);
}

AVLTreePolynom AVLTreePolynom::operator*(const AVLTreePolynom& other) const {
    AVLTreePolynom result;
    multiplyWith(this->root, other, result);
    return result;
}
