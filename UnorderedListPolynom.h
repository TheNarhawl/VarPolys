
#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>

class UnorderedListPolynom {
private:
    struct Term {
        std::unordered_map<char, int> variables;
        double coefficient;
    };
    std::vector<Term> terms;

public:
    void addTerm(double coefficient, const std::map<char, int>& variables);
    double getTerm(const std::map<char, int>& variables) const;
    UnorderedListPolynom operator+(const UnorderedListPolynom& other) const;
    UnorderedListPolynom operator-(const UnorderedListPolynom& other) const;
    UnorderedListPolynom operator*(const UnorderedListPolynom& other) const;
    void print() const;
    void clear();
    std::vector<std::pair<double, std::map<char, int>>> getTerms() const;
};