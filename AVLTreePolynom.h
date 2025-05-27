#pragma once
#include <string>
#include <iostream>
#include <map>

struct Monomial {
    double coefficient;
    std::map<char, int> variables;

    bool operator<(const Monomial& other) const;
    bool operator==(const Monomial& other) const;
    std::string toString() const;
};

struct Node {
    Monomial monom;
    Node* left;
    Node* right;
    int height;

    Node(const Monomial& m);
};

class AVLTreePolynom {
private:
    Node* root;

    Node* insert(Node* node, const Monomial& m);
    Node* rotateLeft(Node* y);
    Node* rotateRight(Node* x);
    int height(Node* n);
    int getBalance(Node* n);
    void inorder(Node* node) const;
    void destroy(Node* node);

public:
    AVLTreePolynom();
    ~AVLTreePolynom();

    void insert(const Monomial& m);
    void print() const;
};
