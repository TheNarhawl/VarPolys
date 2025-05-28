#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

class UnorderedMapArrayPolynom {
private:
    struct Term {
        std::map<char, int> variables;
        double coefficient;

        bool operator==(const Term& other) const {
            return variables == other.variables;
        }
    };

    std::vector<Term> terms;

public:
    void addTerm(double coefficient, const std::map<char, int>& variables);

    UnorderedMapArrayPolynom operator+(const UnorderedMapArrayPolynom& other) const;
    UnorderedMapArrayPolynom operator-(const UnorderedMapArrayPolynom& other) const;
    UnorderedMapArrayPolynom operator*(const UnorderedMapArrayPolynom& other) const;

    void print() const;
    void clear();

    std::vector<std::pair<double, std::map<char, int>>> getTerms() const;
};