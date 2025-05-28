#include <iostream>
#include <chrono>
#include "MultiPolynomStorage.h"

int main() {
    setlocale(LC_ALL, "Russian");

    MultiPolynomStorage p1, p2;

    p1.addTerm(3, { {'x', 2}, {'y', 1} });
    p1.addTerm(4, { {'a', 1} });
    p1.addTerm(-2, { {'x', 1} });

    p2.addTerm(-3, { {'x', 2}, {'y', 1} });
    p2.addTerm(5, { {'a', 1} });
    p2.addTerm(2, { {'x', 1} });

    std::cout << "=== СЛОЖЕНИЕ ===\n";
    MultiPolynomStorage sum = p1 + p2;
    sum.print();

    std::cout << "\n=== ВЫЧИТАНИЕ ===\n";
    MultiPolynomStorage diff = p1 - p2;
    diff.print();

    std::cout << "\n=== УМНОЖЕНИЕ ===\n";
    MultiPolynomStorage prod = p1 * p2;
    prod.print();

    return 0;
}
