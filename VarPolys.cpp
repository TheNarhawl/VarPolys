#include "AVLTreePolynom.h"
#include "OrderedMapPolynom.h"
#include "HashChainPolynom.h"
#include "CollisionResolutionPolynom.h"
#include "UnorderedArrayListPolynom.h"

int main() {
    setlocale(LC_ALL, "Russian");

    // AVL TREE
    {
        std::cout << "USING AVL TREE:" << std::endl;
        AVLTreePolynom poly;

        Monomial m1 = { 3, {{'x', 2}, {'y', 1}} };
        Monomial m2 = { -2, {{'x', 1}, {'y', 2}} };
        Monomial m3 = { 1.5, {{'x', 2}, {'y', 1}} };
        Monomial m4 = { 5, {{'a', 1}} };

        poly.insert(m1);
        poly.insert(m2);
        poly.insert(m3);
        poly.insert(m4);

        poly.print();

        std::cout << "\n" << std::endl;
    }

    // ORDERED MAP
    {
        std::cout << "USING ORDERED MAP:" << std::endl;

        OrderedMapPolynom p1, p2;

        p1.addTerm(3, { {'x', 2}, {'y', 1} });
        p1.addTerm(-2, { {'x', 1}, {'y', 2} });
        p1.addTerm(5, { {'a', 1} });

        std::cout << "Полином 1: ";
        p1.print();

        p2.addTerm(1.5, { {'x', 2}, {'y', 1} });
        p2.addTerm(-5, { {'a', 1} });

        std::cout << "Полином 2: ";
        p2.print();

        OrderedMapPolynom sum = p1 + p2;
        std::cout << "Сумма: ";
        sum.print();

        OrderedMapPolynom diff = p1 - p2;
        std::cout << "Разность: ";
        diff.print();

        std::cout << "\n" << std::endl;
    }

    // UNORDERED ARRAY LIST
    {
        std::cout << "USING UNORDERED ARRAY LIST:" << std::endl;

        UnorderedArrayListPolynom p1, p2;

        p1.addTerm(4, { {'x', 2} });
        p1.addTerm(3, { {'a', 1} });

        p2.addTerm(-2, { {'x', 2} });
        p2.addTerm(5, { {'a', 1} });

        std::cout << "Полином 1: ";
        p1.print();

        std::cout << "Полином 2: ";
        p2.print();

        auto sum = p1 + p2;
        std::cout << "Сумма: ";
        sum.print();

        auto diff = p1 - p2;
        std::cout << "Разность: ";
        diff.print();

        auto prod = p1 * p2;
        std::cout << "Произведение: ";
        prod.print();

        std::cout << "\n" << std::endl;
    }

    // HASH CHAIN
    {
        std::cout << "USING HASH CHAIN:" << std::endl;

        HashChainPolynom p1, p2;
        p1.addTerm(3, { {'x', 2}, {'y', 1} });
        p1.addTerm(4, { {'a', 1} });
        p2.addTerm(2, { {'x', 2}, {'y', 1} });
        p2.addTerm(-4, { {'a', 1} });

        std::cout << "Полином 1: ";
        p1.print();

        std::cout << "Полином 2: ";
        p2.print();

        auto sum = p1 + p2;
        std::cout << "Сумма: ";
        sum.print();

        auto diff = p1 - p2;
        std::cout << "Разность: ";
        diff.print();

        auto product = p1 * p2;
        std::cout << "Произведение: ";
        product.print();

        std::cout << "\n" << std::endl;
    }

    // COLLISION RESOLUTION
    {
        std::cout << "USING COLLISION RESOLUTION:" << std::endl;
        CollisionResolutionPolynom p1, p2;

        p1.addTerm(3, { {'x', 2}, {'y', 1} });
        p1.addTerm(2, { {'b', 1} });

        p2.addTerm(-1, { {'x', 2}, {'y', 1} });
        p2.addTerm(5, { {'b', 1} });

        std::cout << "Полином 1: ";
        p1.print();

        std::cout << "Полином 2: ";
        p2.print();

        auto sum = p1 + p2;
        std::cout << "Сумма: ";
        sum.print();

        auto diff = p1 - p2;
        std::cout << "Разность: ";
        diff.print();

        auto prod = p1 * p2;
        std::cout << "Произведение: ";
        prod.print();

        std::cout << "\n" << std::endl;
    }

    return 0;
}
