#include "UnorderedArrayListPolynom.h"
#include <sstream>

void UnorderedArrayListPolynom::addTerm(double coefficient, const std::map<char, int>& variables) {
    if (coefficient == 0) return;

    for (auto& term : terms) {
        if (term.variables == variables) {
            term.coefficient += coefficient;
            if (term.coefficient == 0) {
                term = terms.back();
                terms.pop_back();
            }
            return;
        }
    }

    terms.push_back({ variables, coefficient });
}

UnorderedArrayListPolynom UnorderedArrayListPolynom::operator+(const UnorderedArrayListPolynom& other) const {
    UnorderedArrayListPolynom result = *this;
    for (const auto& term : other.terms) {
        result.addTerm(term.coefficient, term.variables);
    }
    return result;
}

UnorderedArrayListPolynom UnorderedArrayListPolynom::operator-(const UnorderedArrayListPolynom& other) const {
    UnorderedArrayListPolynom result = *this;
    for (const auto& term : other.terms) {
        result.addTerm(-term.coefficient, term.variables);
    }
    return result;
}

UnorderedArrayListPolynom UnorderedArrayListPolynom::operator*(const UnorderedArrayListPolynom& other) const {
    UnorderedArrayListPolynom result;
    for (const auto& a : terms) {
        for (const auto& b : other.terms) {
            std::map<char, int> newVars = a.variables;
            for (const auto& [var, exp] : b.variables) {
                newVars[var] += exp;
            }
            result.addTerm(a.coefficient * b.coefficient, newVars);
        }
    }
    return result;
}

void UnorderedArrayListPolynom::print() const {
    std::ostringstream oss;
    bool first = true;
    for (const auto& term : terms) {
        if (!first && term.coefficient >= 0) oss << "+";
        oss << term.coefficient;
        for (const auto& [var, exp] : term.variables) {
            oss << var;
            if (exp != 1) oss << "^" << exp;
        }
        oss << " ";
        first = false;
    }
    std::cout << (first ? "0" : oss.str()) << std::endl;
}
