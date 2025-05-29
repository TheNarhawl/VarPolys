#pragma once
#include <iostream>
#include <vector>
#include <optional>
#include <map>
#include <string>

class CollisionResolutionPolynom {
private:
    struct Node {
        std::map<char, int> variables;
        double coefficient;

        bool operator==(const Node& other) const {
            return variables == other.variables;
        }
    };

    std::vector<std::optional<Node>> table;
    size_t capacity;
    size_t size;

    size_t hash(const std::map<char, int>& variables) const;
    void rehash();

public:
    explicit CollisionResolutionPolynom(size_t cap = 101);

    void addTerm(double coefficient, const std::map<char, int>& variables);
    std::optional<Node> getTerm(const std::map<char, int>& variables) const;

    CollisionResolutionPolynom operator+(const CollisionResolutionPolynom& other) const;
    CollisionResolutionPolynom operator-(const CollisionResolutionPolynom& other) const;
    CollisionResolutionPolynom operator*(const CollisionResolutionPolynom& other) const;

    void print() const;
    void clear();

    std::vector<Node> getTerms() const;
};
