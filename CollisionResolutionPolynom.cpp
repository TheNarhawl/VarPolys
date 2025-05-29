#include "CollisionResolutionPolynom.h"
#include <sstream>

CollisionResolutionPolynom::CollisionResolutionPolynom(size_t cap)
    : capacity(cap), size(0), table(cap) {
}

size_t CollisionResolutionPolynom::hash(const std::map<char, int>& variables) const {
    size_t h = 0;
    for (const auto& [var, exp] : variables) {
        // Комбинируем хеши переменных и степеней
        h ^= std::hash<char>()(var) ^ (std::hash<int>()(exp << 1));
    }
    return h % capacity; // Получаем индекс по модулю размера таблицы
}

void CollisionResolutionPolynom::addTerm(double coefficient, const std::map<char, int>& variables) {
    if (coefficient == 0) return;

    size_t idx = hash(variables);
    size_t originalIdx = idx;
    while (true) { // Свободная ячейка
        if (!table[idx].has_value()) { // Терм с такими же переменными найден
            table[idx] = Node{ variables, coefficient };
            ++size;
            return;
        }
        if (table[idx]->variables == variables) {
            table[idx]->coefficient += coefficient;
            if (table[idx]->coefficient == 0) { // Если коэффициент стал 0 — удаляем терм
                table[idx].reset();
                --size;
            }
            return;
        }
        idx = (idx + 1) % capacity;
        if (idx == originalIdx) break; // Если вернулись к исходному индексу — таблица заполнена
    }

    std::cerr << "full hash table" << std::endl;
}

CollisionResolutionPolynom CollisionResolutionPolynom::operator+(const CollisionResolutionPolynom& other) const {
    CollisionResolutionPolynom result = *this;
    for (const auto& optNode : other.table) {
        if (optNode.has_value()) {
            result.addTerm(optNode->coefficient, optNode->variables);
        }
    }
    return result;
}

CollisionResolutionPolynom CollisionResolutionPolynom::operator-(const CollisionResolutionPolynom& other) const {
    CollisionResolutionPolynom result = *this;
    for (const auto& optNode : other.table) {
        if (optNode.has_value()) {
            result.addTerm(-optNode->coefficient, optNode->variables);
        }
    }
    return result;
}

CollisionResolutionPolynom CollisionResolutionPolynom::operator*(const CollisionResolutionPolynom& other) const {
    CollisionResolutionPolynom result;

    for (const auto& a : this->table) {
        if (!a.has_value()) continue;
        for (const auto& b : other.table) {
            if (!b.has_value()) continue;

            std::map<char, int> newVars = a->variables;
            for (const auto& [var, exp] : b->variables) {
                newVars[var] += exp;
            }
            result.addTerm(a->coefficient * b->coefficient, newVars);
        }
    }

    return result;
}

void CollisionResolutionPolynom::print() const {
    bool isFirstTerm = true;
    bool hasTerms = false;

    for (const auto& optNode : table) {
        if (!optNode.has_value()) continue;

        const auto& node = optNode.value();
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

    if (!hasTerms) {
        std::cout << "0";
    }

    std::cout << std::endl;
}

void CollisionResolutionPolynom::clear() {
    table.clear();
    table.resize(capacity);
    size = 0;
}

std::vector<CollisionResolutionPolynom::Node> CollisionResolutionPolynom::getTerms() const {
    std::vector<Node> terms;
    for (const auto& optNode : table) {
        if (optNode.has_value() && optNode->coefficient != 0) {
            terms.push_back(optNode.value());
        }
    }
    return terms;
}


