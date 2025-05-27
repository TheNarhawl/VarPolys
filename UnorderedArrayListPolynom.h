#pragma once
#include <vector>
#include <map>
#include <iostream>

class UnorderedArrayListPolynom {
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
    UnorderedArrayListPolynom operator+(const UnorderedArrayListPolynom& other) const;
    UnorderedArrayListPolynom operator-(const UnorderedArrayListPolynom& other) const;
    UnorderedArrayListPolynom operator*(const UnorderedArrayListPolynom& other) const;

    void print() const;
};
