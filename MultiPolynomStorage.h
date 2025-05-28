#pragma once

#include "AVLTreePolynom.h"
#include "CollisionResolutionPolynom.h"
#include "HashChainPolynom.h"
#include "OrderedMapPolynom.h"
#include "UnorderedListPolynom.h"
#include "UnorderedMapArrayPolynom.h"
#include <map>
#include <unordered_map>
#include <iostream>

class MultiPolynomStorage {
public:
    AVLTreePolynom avlTree;
    CollisionResolutionPolynom collisionHash;
    HashChainPolynom hashChain;
    OrderedMapPolynom orderedMap;
    UnorderedListPolynom unorderedList;
    UnorderedMapArrayPolynom unorderedMapArray;

    void clear() {
        avlTree.clear();
        collisionHash.clear();
        hashChain.clear();
        orderedMap.clear();
        unorderedList.clear();
        unorderedMapArray.clear();
    }

    void addTerm(double coefficient, const std::map<char, int>& variables) {
        avlTree.addTerm(coefficient, variables);
        collisionHash.addTerm(coefficient, variables);
        hashChain.addTerm(coefficient, variables);
        orderedMap.addTerm(coefficient, variables);
        unorderedList.addTerm(coefficient, variables);
        unorderedMapArray.addTerm(coefficient, variables);
    }

    MultiPolynomStorage operator+(const MultiPolynomStorage& other) const {
        MultiPolynomStorage result;
        result.avlTree = avlTree + other.avlTree;
        result.collisionHash = collisionHash + other.collisionHash;
        result.hashChain = hashChain + other.hashChain;
        result.orderedMap = orderedMap + other.orderedMap;
        result.unorderedList = unorderedList + other.unorderedList;
        result.unorderedMapArray = unorderedMapArray + other.unorderedMapArray;
        return result;
    }

    MultiPolynomStorage operator-(const MultiPolynomStorage& other) const {
        MultiPolynomStorage result;
        result.avlTree = avlTree - other.avlTree;
        result.collisionHash = collisionHash - other.collisionHash;
        result.hashChain = hashChain - other.hashChain;
        result.orderedMap = orderedMap - other.orderedMap;
        result.unorderedList = unorderedList - other.unorderedList;
        result.unorderedMapArray = unorderedMapArray - other.unorderedMapArray;
        return result;
    }

    MultiPolynomStorage operator*(const MultiPolynomStorage& other) const {
        MultiPolynomStorage result;
        result.avlTree = avlTree * other.avlTree;
        result.collisionHash = collisionHash * other.collisionHash;
        result.hashChain = hashChain * other.hashChain;
        result.orderedMap = orderedMap * other.orderedMap;
        result.unorderedList = unorderedList * other.unorderedList;
        result.unorderedMapArray = unorderedMapArray * other.unorderedMapArray;
        return result;
    }

    void print() const {
        std::cout << "====== MULTI STRUCTURE POLYNOM PRINT ======\n";

        std::cout << "[AVLTree]:\n"; avlTree.print();
        std::cout << "[CollisionResolution]:\n"; collisionHash.print();
        std::cout << "[HashChain]:\n"; hashChain.print();
        std::cout << "[OrderedMap]:\n"; orderedMap.print();
        std::cout << "[UnorderedList]:\n"; unorderedList.print();
        std::cout << "[UnorderedMapArray]:\n"; unorderedMapArray.print();

        std::cout << "==========================================\n";
    }

    /*double evaluate(const std::unordered_map<std::string, double>& vars) const {
        return orderedMap.evaluate(vars);
    }*/
};
