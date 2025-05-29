#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>

class UnorderedMapArrayPolynom {
private:
    struct Term {
        std::unordered_map<char, int> variables;
        double coefficient;
    };
    std::vector<Term> terms;

public:
    void addTerm(double coefficient, const std::map<char, int>& variables);
    double getTerm(const std::map<char, int>& variables) const;
    UnorderedMapArrayPolynom operator+(const UnorderedMapArrayPolynom& other) const;
    UnorderedMapArrayPolynom operator-(const UnorderedMapArrayPolynom& other) const;
    UnorderedMapArrayPolynom operator*(const UnorderedMapArrayPolynom& other) const;

    void print() const;
    void clear();

    std::vector<std::pair<double, std::map<char, int>>> getTerms() const;
};