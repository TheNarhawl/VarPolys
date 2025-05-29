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

std::optional<HashChainPolynom::Node> HashChainPolynom::getTerm(const std::map<char, int>& variables) const {
    size_t idx = hash(variables);
    for (const auto& node : table[idx]) {
        if (isEqual(node.variables, variables)) {
            return node;
        }
    }
    return std::nullopt;
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
    bool isFirstTerm = true;
    bool hasTerms = false;

    for (const auto& bucket : table) {
        for (const auto& node : bucket) {
            if (node.coefficient == 0) continue;

            hasTerms = true;

            if (!isFirstTerm) {
                std::cout << (node.coefficient >= 0 ? " + " : " - ");
            }
            else {
                if (node.coefficient < 0) std::cout << "-";
            }

            double absCoeff = std::abs(node.coefficient);

            if (absCoeff != 1.0 || node.variables.empty()) {
                std::cout << absCoeff;
            }

            for (const auto& [var, exp] : node.variables) {
                std::cout << var;
                if (exp != 1) std::cout << "^" << exp;
            }

            isFirstTerm = false;
        }
    }

    if (!hasTerms) {
        std::cout << "0";
    }

    std::cout << std::endl;
}

void HashChainPolynom::clear() {
    for (auto& chain : table) {
        chain.clear();
    }
}

std::vector<HashChainPolynom::Node> HashChainPolynom::getTerms() const {
    std::vector<Node> terms;
    for (const auto& chain : table) {
        for (const auto& node : chain) {
            if (node.coefficient != 0) {
                terms.push_back(node);
            }
        }
    }
    return terms;
}

