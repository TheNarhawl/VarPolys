#include "AVLTreePolynom.h"

int main() {

    // AVL TREE
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

    return 0;
}
