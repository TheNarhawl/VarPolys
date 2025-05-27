#include "AVLTreePolynom.h"
#include "OrderedMapPolynom.h"
#include "HashChainPolynom.h"
#include "CollisionResolutionPolynom.h"
#include "UnorderedListPolynom.h"
#include "UnorderedMapArrayPolynom.h"
#include <chrono>

int main() {
    setlocale(LC_ALL, "Russian");

    // Термы: p1 = 3x²y + 4a - 2x
    //        p2 = -3x²y + 5a + 2x

    // USING ORDERED MAP
    {
        std::cout << "USING ORDERED MAP:" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();

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

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Время выполнения: " << duration.count() << " микросекунд\n\n";

        std::cout << "\n" << std::endl;
    }

    // USING UNORDERED LIST
    {
        std::cout << "USING UNORDERED LIST:" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();

        UnorderedListPolynom p1, p2;
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

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Время выполнения: " << duration.count() << " микросекунд\n\n";

        std::cout << "\n" << std::endl;
    }

    // USING UNORDERED ARRAY
    {
        std::cout << "USING UNORDERED ARRAY:" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();

        UnorderedMapArrayPolynom p1, p2;

        p1.addTerm(3, { {'x', 2}, {'y', 1} });
        p1.addTerm(-2, { {'x', 1} });
        p1.addTerm(4, { {'a', 1} });

        p2.addTerm(-3, { {'x', 2}, {'y', 1} });
        p2.addTerm(5, { {'a', 1} });
        p2.addTerm(2, { {'x', 1} });

        std::cout << "Полином 1: "; p1.print();
        std::cout << "Полином 2: "; p2.print();

        auto sum = p1 + p2;
        std::cout << "Сумма: "; sum.print();

        auto diff = p1 - p2;
        std::cout << "Разность: "; diff.print();

        auto prod = p1 * p2;
        std::cout << "Произведение: "; prod.print();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Время выполнения: " << duration.count() << " микросекунд\n\n";

        std::cout << "\n" << std::endl;
    }

    // USING HASH CHAIN
    {
        std::cout << "USING HASH CHAIN:" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();

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

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Время выполнения: " << duration.count() << " микросекунд\n\n";

        std::cout << "\n" << std::endl;
    }

    // USING COLLISION RESOLUTION
    {
        std::cout << "USING COLLISION RESOLUTION:" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();

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

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Время выполнения: " << duration.count() << " микросекунд\n\n";

        std::cout << "\n" << std::endl;
    }

    // USING AVL TREE
    {
        std::cout << "USING AVL TREE:" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();

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

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Время выполнения: " << duration.count() << " микросекунд\n\n";

        std::cout << "\n" << std::endl;
    }

    return 0;
}
