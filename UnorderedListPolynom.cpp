#include "UnorderedListPolynom.h"

void UnorderedListPolynom::addTerm(double coefficient, const std::map<char, int>& variables) {
    if (coefficient == 0.0) return;

    auto it = std::find_if(terms.begin(), terms.end(),
        [&](const Term& term) { return term.variables == variables; });

    if (it != terms.end()) {
        it->coefficient += coefficient;
        if (it->coefficient == 0.0) {
            terms.erase(it);
        }
    }
    else {
        terms.push_back({ variables, coefficient });
    }
}

UnorderedListPolynom UnorderedListPolynom::operator+(const UnorderedListPolynom& other) const {
    UnorderedListPolynom result = *this;
    for (const auto& term : other.terms) {
        result.addTerm(term.coefficient, term.variables);
    }
    return result;
}

UnorderedListPolynom UnorderedListPolynom::operator-(const UnorderedListPolynom& other) const {
    UnorderedListPolynom result = *this;
    for (const auto& term : other.terms) {
        result.addTerm(-term.coefficient, term.variables);
    }
    return result;
}

UnorderedListPolynom UnorderedListPolynom::operator*(const UnorderedListPolynom& other) const {
    UnorderedListPolynom result;
    for (const auto& term1 : this->terms) {
        for (const auto& term2 : other.terms) {
            std::map<char, int> newVars = term1.variables;
            for (const auto& [var, exp] : term2.variables) {
                newVars[var] += exp;
            }
            result.addTerm(term1.coefficient * term2.coefficient, newVars);
        }
    }
    return result;
}

void UnorderedListPolynom::print() const {
    if (terms.empty()) {
        std::cout << "0";
        return;
    }

    bool isFirstTerm = true;
    for (const auto& term : terms) {
        if (!isFirstTerm) {
            std::cout << (term.coefficient >= 0 ? " + " : " - ");
        }
        else if (term.coefficient < 0) {
            std::cout << "-";
        }
        isFirstTerm = false;

        double absCoeff = std::abs(term.coefficient);
        if (absCoeff != 1.0 || term.variables.empty()) {
            std::cout << absCoeff;
        }

        for (const auto& [var, exp] : term.variables) {
            std::cout << var;
            if (exp != 1) std::cout << "^" << exp;
        }
    }
    std::cout << std::endl;
}