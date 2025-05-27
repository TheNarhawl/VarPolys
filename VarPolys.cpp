#include "AVLTreePolynom.h"
#include "OrderedMapPolynom.h"
#include "HashChainPolynom.h"
#include "CollisionResolutionPolynom.h"
#include "UnorderedArrayListPolynom.h"

int main() {
    setlocale(LC_ALL, "Russian");

    // Термы: p1 = 3x²y + 4a - 2x
    //        p2 = -3x²y + 5a + 2x

    // USING AVL TREE
    {
        std::cout << "USING AVL TREE:" << std::endl;
        AVLTreePolynom p1, p2;
        p1.insert({ { {'x', 2}, {'y', 1} }, 3 });
        p1.insert({ { {'a', 1} }, 4 });
        p1.insert({ { {'x', 1} }, -2 });

        p2.insert({ { {'x', 2}, {'y', 1} }, -3 });
        p2.insert({ { {'a', 1} }, 5 });
        p2.insert({ { {'x', 1} }, 2 });

        std::cout << "Полином 1: "; p1.print();
        std::cout << "Полином 2: "; p2.print();

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

    // USING ORDERED MAP
    {
        std::cout << "USING ORDERED MAP:" << std::endl;
        OrderedMapPolynom p1, p2;
        p1.addTerm(3, { {'x', 2}, {'y', 1} });
        p1.addTerm(4, { {'a', 1} });
        p1.addTerm(-2, { {'x', 1} });

        p2.addTerm(-3, { {'x', 2}, {'y', 1} });
        p2.addTerm(5, { {'a', 1} });
        p2.addTerm(2, { {'x', 1} });

        std::cout << "Полином 1: "; p1.print();
        std::cout << "Полином 2: "; p2.print();

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

    // USING UNORDERED ARRAY LIST
    {
        std::cout << "USING UNORDERED ARRAY LIST:" << std::endl;
        UnorderedArrayListPolynom p1, p2;
        p1.addTerm(3, { {'x', 2}, {'y', 1} });
        p1.addTerm(4, { {'a', 1} });
        p1.addTerm(-2, { {'x', 1} });

        p2.addTerm(-3, { {'x', 2}, {'y', 1} });
        p2.addTerm(5, { {'a', 1} });
        p2.addTerm(2, { {'x', 1} });

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

    // USING HASH CHAIN
    {
        std::cout << "USING HASH CHAIN:" << std::endl;
        HashChainPolynom p1, p2;
        p1.addTerm(3, { {'x', 2}, {'y', 1} });
        p1.addTerm(4, { {'a', 1} });
        p1.addTerm(-2, { {'x', 1} });

        p2.addTerm(-3, { {'x', 2}, {'y', 1} });
        p2.addTerm(5, { {'a', 1} });
        p2.addTerm(2, { {'x', 1} });

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

    // USING COLLISION RESOLUTION
    {
        std::cout << "USING COLLISION RESOLUTION:" << std::endl;
        CollisionResolutionPolynom p1, p2;
        p1.addTerm(3, { {'x', 2}, {'y', 1} });
        p1.addTerm(4, { {'a', 1} });
        p1.addTerm(-2, { {'x', 1} });

        p2.addTerm(-3, { {'x', 2}, {'y', 1} });
        p2.addTerm(5, { {'a', 1} });
        p2.addTerm(2, { {'x', 1} });

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
