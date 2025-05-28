#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>

class HashChainPolynom {
private:
    struct Node {
        std::map<char, int> variables;
        double coefficient;

        bool operator==(const Node& other) const {
            return variables == other.variables && coefficient == other.coefficient;
        }
    };

    std::vector<std::list<Node>> table;
    size_t capacity;

    size_t hash(const std::map<char, int>& variables) const;
    bool isEqual(const std::map<char, int>& a, const std::map<char, int>& b) const;

public:
    explicit HashChainPolynom(size_t cap = 101);

    void addTerm(double coefficient, const std::map<char, int>& variables);
    HashChainPolynom operator+(const HashChainPolynom& other) const;
    HashChainPolynom operator-(const HashChainPolynom& other) const;
    HashChainPolynom operator*(const HashChainPolynom& other) const;

    void print() const;
    void clear();

    std::vector<Node> getTerms() const;
};
