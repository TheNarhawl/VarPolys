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
    CollisionResolutionPolynom collisionResolution;
    HashChainPolynom hashChain;
    OrderedMapPolynom orderedMap;
    UnorderedListPolynom unorderedList;
    UnorderedMapArrayPolynom unorderedMapArray;


    std::vector<std::pair<double, std::map<char, int>>> getTermsFrom(const std::string& polyType) const {
        std::vector<std::pair<double, std::map<char, int>>> result;

        if (polyType == "avlTree") {
            auto terms = avlTree.getTerms();
            for (const auto& term : terms) {
                if (term.coefficient != 0)
                    result.emplace_back(term.coefficient, term.variables);
            }
        }
        else if (polyType == "collisionResolution") {
            auto terms = collisionResolution.getTerms();
            for (const auto& node : terms) {
                if (node.coefficient != 0)
                    result.emplace_back(node.coefficient, node.variables);
            }
        }
        else if (polyType == "hashChain") {
            auto terms = hashChain.getTerms();
            for (const auto& node : terms) {
                if (node.coefficient != 0)
                    result.emplace_back(node.coefficient, node.variables);
            }
        }
        else if (polyType == "orderedMap") {
            auto terms = orderedMap.getTerms();
            for (const auto& [coeff, vars] : terms) {
                if (coeff != 0)
                    result.emplace_back(coeff, vars);
            }
        }
        else if (polyType == "unorderedList") {
            auto terms = unorderedList.getTerms();
            for (const auto& [coeff, vars] : terms) {
                if (coeff != 0)
                    result.emplace_back(coeff, vars);
            }
        }
        else if (polyType == "unorderedMapArray") {
            auto terms = unorderedMapArray.getTerms();
            for (const auto& [coeff, vars] : terms) {
                if (coeff != 0)
                    result.emplace_back(coeff, vars);
            }
        }

        return result;
    }


    void clear() {
        avlTree.clear();
        collisionResolution.clear();
        hashChain.clear();
        orderedMap.clear();
        unorderedList.clear();
        unorderedMapArray.clear();
    }

    void addTerm(double coefficient, const std::map<char, int>& variables) {
        avlTree.addTerm(coefficient, variables);
        collisionResolution.addTerm(coefficient, variables);
        hashChain.addTerm(coefficient, variables);
        orderedMap.addTerm(coefficient, variables);
        unorderedList.addTerm(coefficient, variables);
        unorderedMapArray.addTerm(coefficient, variables);
    }


    MultiPolynomStorage operator+(const MultiPolynomStorage& other) const {
        MultiPolynomStorage result;
        result.avlTree = avlTree + other.avlTree;
        result.collisionResolution = collisionResolution + other.collisionResolution;
        result.hashChain = hashChain + other.hashChain;
        result.orderedMap = orderedMap + other.orderedMap;
        result.unorderedList = unorderedList + other.unorderedList;
        result.unorderedMapArray = unorderedMapArray + other.unorderedMapArray;
        return result;
    }

    MultiPolynomStorage operator-(const MultiPolynomStorage& other) const {
        MultiPolynomStorage result;
        result.avlTree = avlTree - other.avlTree;
        result.collisionResolution = collisionResolution - other.collisionResolution;
        result.hashChain = hashChain - other.hashChain;
        result.orderedMap = orderedMap - other.orderedMap;
        result.unorderedList = unorderedList - other.unorderedList;
        result.unorderedMapArray = unorderedMapArray - other.unorderedMapArray;
        return result;
    }

    MultiPolynomStorage operator*(const MultiPolynomStorage& other) const {
        MultiPolynomStorage result;
        result.avlTree = avlTree * other.avlTree;
        result.collisionResolution = collisionResolution * other.collisionResolution;
        result.hashChain = hashChain * other.hashChain;
        result.orderedMap = orderedMap * other.orderedMap;
        result.unorderedList = unorderedList * other.unorderedList;
        result.unorderedMapArray = unorderedMapArray * other.unorderedMapArray;
        return result;
    }

    void print() const {
        std::cout << "====== MULTI STRUCTURE POLYNOM PRINT ======\n";

        std::cout << "[AVLTree]:\n"; avlTree.print();
        std::cout << "[CollisionResolution]:\n"; collisionResolution.print();
        std::cout << "[HashChain]:\n"; hashChain.print();
        std::cout << "[OrderedMap]:\n"; orderedMap.print();
        std::cout << "[UnorderedList]:\n"; unorderedList.print();
        std::cout << "[UnorderedMapArray]:\n"; unorderedMapArray.print();

        std::cout << "==========================================\n";
    }
};
