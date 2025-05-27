#pragma once
#include <map>
#include <iostream>
#include <string>
#include <sstream>

struct Monomial {
    std::map<char, int> variables;
    double coefficient;

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
    Node* root;

    void destroy(Node* node);
    int height(Node* n);
    int getBalance(Node* n);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insert(Node* node, const Monomial& m);
    void inorder(Node* node) const;

    void traverseAndInsert(Node* node, AVLTreePolynom& target, double sign) const;
    void multiplyWith(Node* a, const AVLTreePolynom& other, AVLTreePolynom& result) const;
    void multiplyByMonomial(Node* b, const Monomial& m, AVLTreePolynom& result) const;

public:
    AVLTreePolynom();
    ~AVLTreePolynom();

    void insert(const Monomial& m);
    void print() const;
    void printInOrder(Node* node, bool& isFirstTerm) const;


    AVLTreePolynom operator+(const AVLTreePolynom& other) const;
    AVLTreePolynom operator-(const AVLTreePolynom& other) const;
    AVLTreePolynom operator*(const AVLTreePolynom& other) const;
};