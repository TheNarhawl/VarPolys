#pragma once
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <optional>

using VariableKey = std::map<char, int>;

class OrderedMapPolynom {
private:
    std::map<VariableKey, double> terms;

public:
    OrderedMapPolynom() = default;

    void addTerm(double coefficient, const VariableKey& variables);
    std::string toString() const;

    double getTerm(const VariableKey& variables) const;
    OrderedMapPolynom operator+(const OrderedMapPolynom& other) const;
    OrderedMapPolynom operator-(const OrderedMapPolynom& other) const;
    OrderedMapPolynom operator*(const OrderedMapPolynom& other) const;

    void print() const;
    void clear();

    std::vector<std::pair<double, VariableKey>> getTerms() const;
};
