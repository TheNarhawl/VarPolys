#pragma once
#include <list>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>

class UnorderedListPolynom {
private:
    struct Term {
        std::map<char, int> variables;
        double coefficient;

        bool operator==(const Term& other) const {
            return variables == other.variables;
        }
    };

    std::list<Term> terms;

public:
    void addTerm(double coefficient, const std::map<char, int>& variables);

    UnorderedListPolynom operator+(const UnorderedListPolynom& other) const;
    UnorderedListPolynom operator-(const UnorderedListPolynom& other) const;
    UnorderedListPolynom operator*(const UnorderedListPolynom& other) const;

    void print() const;
    void clear();
};