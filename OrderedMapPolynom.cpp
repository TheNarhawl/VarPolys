#include "OrderedMapPolynom.h"
#include <sstream>

void OrderedMapPolynom::addTerm(double coefficient, const VariableKey& variables) {
    if (coefficient == 0) return;
    terms[variables] += coefficient;
    if (terms[variables] == 0) {
        terms.erase(variables);
    }
}

std::string OrderedMapPolynom::toString() const {
    if (terms.empty()) return "0";

    std::ostringstream oss;
    for (const auto& [vars, coef] : terms) {
        if (coef >= 0 && oss.tellp() > 0) oss << "+";
        oss << coef;
        for (const auto& [var, exp] : vars) {
            oss << var;
            if (exp != 1) oss << "^" << exp;
        }
        oss << " ";
    }
    return oss.str();
}

void OrderedMapPolynom::print() const {
    std::cout << toString() << std::endl;
}

OrderedMapPolynom OrderedMapPolynom::operator+(const OrderedMapPolynom& other) const {
    OrderedMapPolynom result = *this;
    for (const auto& [vars, coef] : other.terms) {
        result.addTerm(coef, vars);
    }
    return result;
}

OrderedMapPolynom OrderedMapPolynom::operator-(const OrderedMapPolynom& other) const {
    OrderedMapPolynom result = *this;
    for (const auto& [vars, coef] : other.terms) {
        result.addTerm(-coef, vars);
    }
    return result;
}

OrderedMapPolynom OrderedMapPolynom::operator*(const OrderedMapPolynom& other) const {
    OrderedMapPolynom result;

    for (const auto& [vars1, coef1] : this->terms) {
        for (const auto& [vars2, coef2] : other.terms) {
            VariableKey newVars = vars1;

            for (const auto& [var, exp] : vars2) {
                newVars[var] += exp;
            }

            result.addTerm(coef1 * coef2, newVars);
        }
    }

    return result;
}

