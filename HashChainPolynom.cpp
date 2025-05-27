#include "HashChainPolynom.h"
#include <sstream>

HashChainPolynom::HashChainPolynom(size_t cap) : capacity(cap), table(cap) {}

size_t HashChainPolynom::hash(const std::map<char, int>& variables) const {
    size_t h = 0;
    for (const auto& [var, exp] : variables) {
        h ^= std::hash<char>()(var) ^ std::hash<int>()(exp << 1);
    }
    return h % capacity;
}

bool HashChainPolynom::isEqual(const std::map<char, int>& a, const std::map<char, int>& b) const {
    return a == b;
}

void HashChainPolynom::addTerm(double coefficient, const std::map<char, int>& variables) {
    if (coefficient == 0) return;

    size_t idx = hash(variables);
    for (auto& node : table[idx]) {
        if (isEqual(node.variables, variables)) {
            node.coefficient += coefficient;
            if (node.coefficient == 0) {
                table[idx].remove(node);
            }
            return;
        }
    }
    table[idx].push_back({ variables, coefficient });
}

HashChainPolynom HashChainPolynom::operator+(const HashChainPolynom& other) const {
    HashChainPolynom result = *this;
    for (const auto& bucket : other.table) {
        for (const auto& node : bucket) {
            result.addTerm(node.coefficient, node.variables);
        }
    }
    return result;
}

HashChainPolynom HashChainPolynom::operator-(const HashChainPolynom& other) const {
    HashChainPolynom result = *this;
    for (const auto& bucket : other.table) {
        for (const auto& node : bucket) {
            result.addTerm(-node.coefficient, node.variables);
        }
    }
    return result;
}

HashChainPolynom HashChainPolynom::operator*(const HashChainPolynom& other) const {
    HashChainPolynom result;

    for (const auto& bucket1 : this->table) {
        for (const auto& node1 : bucket1) {
            for (const auto& bucket2 : other.table) {
                for (const auto& node2 : bucket2) {
                    std::map<char, int> newVars = node1.variables;
                    for (const auto& [var, exp] : node2.variables) {
                        newVars[var] += exp;
                    }
                    result.addTerm(node1.coefficient * node2.coefficient, newVars);
                }
            }
        }
    }

    return result;
}

void HashChainPolynom::print() const {
    std::ostringstream oss;
    bool first = true;
    for (const auto& bucket : table) {
        for (const auto& node : bucket) {
            if (!first && node.coefficient >= 0) oss << "+";
            oss << node.coefficient;
            for (const auto& [var, exp] : node.variables) {
                oss << var;
                if (exp != 1) oss << "^" << exp;
            }
            oss << " ";
            first = false;
        }
    }
    std::cout << (first ? "0" : oss.str()) << std::endl;
}
