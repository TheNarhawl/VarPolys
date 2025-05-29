#include "UnorderedMapArrayPolynom.h"

void UnorderedMapArrayPolynom::addTerm(double coefficient, const std::map<char, int>& variables) {
    if (coefficient == 0.0) return;

    std::unordered_map<char, int> unorderedVars(variables.begin(), variables.end());

    auto it = std::find_if(terms.begin(), terms.end(),
        [&](const Term& term) { return term.variables == unorderedVars; });

    if (it != terms.end()) {
        it->coefficient += coefficient;
        if (it->coefficient == 0.0) {
            *it = terms.back();
            terms.pop_back();
        }
    }
    else {
        terms.push_back({ unorderedVars, coefficient });
    }
}

double UnorderedMapArrayPolynom::getTerm(const std::map<char, int>& variables) const {
    std::unordered_map<char, int> unorderedVars(variables.begin(), variables.end());
    auto it = std::find_if(terms.begin(), terms.end(),
        [&](const Term& term) { return term.variables == unorderedVars; });
    return (it != terms.end()) ? it->coefficient : 0.0;
}

UnorderedMapArrayPolynom UnorderedMapArrayPolynom::operator+(const UnorderedMapArrayPolynom& other) const {
    UnorderedMapArrayPolynom result = *this;
    for (const auto& term : other.terms) {
        result.addTerm(term.coefficient, std::map<char, int>(term.variables.begin(), term.variables.end()));
    }
    return result;
}

UnorderedMapArrayPolynom UnorderedMapArrayPolynom::operator-(const UnorderedMapArrayPolynom& other) const {
    UnorderedMapArrayPolynom result = *this;
    for (const auto& term : other.terms) {
        result.addTerm(-term.coefficient, std::map<char, int>(term.variables.begin(), term.variables.end()));
    }
    return result;
}

UnorderedMapArrayPolynom UnorderedMapArrayPolynom::operator*(const UnorderedMapArrayPolynom& other) const {
    UnorderedMapArrayPolynom result;
    for (const auto& term1 : this->terms) {
        for (const auto& term2 : other.terms) {
            std::unordered_map<char, int> newVars = term1.variables;
            for (const auto& [var, exp] : term2.variables) {
                newVars[var] += exp;
            }
            result.addTerm(term1.coefficient * term2.coefficient,
                std::map<char, int>(newVars.begin(), newVars.end()));
        }
    }
    return result;
}

void UnorderedMapArrayPolynom::print() const {
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

void UnorderedMapArrayPolynom::clear() {
    terms.clear();
}

std::vector<std::pair<double, std::map<char, int>>> UnorderedMapArrayPolynom::getTerms() const {
    std::vector<std::pair<double, std::map<char, int>>> result;
    for (const auto& term : terms) {
        if (term.coefficient != 0) {
            std::map<char, int> orderedVars(term.variables.begin(), term.variables.end());
            result.emplace_back(term.coefficient, orderedVars);
        }
    }
    return result;
}