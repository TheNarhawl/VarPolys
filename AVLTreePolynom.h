#pragma once

#include <map>
#include <vector>
#include <iostream>

class AVLTreePolynom {
private:
    struct Term {
        std::map<char, int> variables;
        double coefficient;

        Term(double coeff, const std::map<char, int>& vars);
        bool operator<(const Term& other) const;
        bool operator==(const Term& other) const;
    };

    struct AVLNode {
        Term term;
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode(const Term& t);
    };

    AVLNode* root;
    size_t size;

    int height(AVLNode* node) const;
    int balanceFactor(AVLNode* node) const;
    void updateHeight(AVLNode* node);

    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* balance(AVLNode* node);
    const Term* findTermRecursive(AVLNode* node, const std::map<char, int>& variables) const;

    AVLNode* insert(AVLNode* node, const Term& term);
    AVLNode* remove(AVLNode* node, const Term& term);
    AVLNode* findMin(AVLNode* node) const;
    void inOrderTraversal(AVLNode* node, std::vector<Term>& terms) const;
    void clear(AVLNode* node);
    AVLNode* copyTree(AVLNode* node) const;

public:
    AVLTreePolynom();
    AVLTreePolynom(const AVLTreePolynom& other);
    AVLTreePolynom(AVLTreePolynom&& other) noexcept;
    AVLTreePolynom& operator=(const AVLTreePolynom& other);
    AVLTreePolynom& operator=(AVLTreePolynom&& other) noexcept;
    ~AVLTreePolynom();

    void addTerm(double coefficient, const std::map<char, int>& variables);
    const Term* findTerm(const std::map<char, int>& variables) const;
    AVLTreePolynom operator+(const AVLTreePolynom& other) const;
    AVLTreePolynom operator-(const AVLTreePolynom& other) const;
    AVLTreePolynom operator*(const AVLTreePolynom& other) const;
    void print() const;
    void clear();
    size_t getSize() const;

    std::vector<Term> getTerms() const;
};
