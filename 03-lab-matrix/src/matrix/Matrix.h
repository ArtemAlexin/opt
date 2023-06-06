#pragma once

#include "CanonicalMatrix.h"
#include "Vector.h"

struct Matrix {
    virtual double get(size_t i, size_t j) const = 0;

    virtual void set(size_t i, size_t j, double value) = 0;

    virtual size_t size() const = 0;

    virtual Vector operator*(const Vector &v) const = 0;

    virtual ~Matrix() = default;
};

template<typename T>
inline T readFromFile(const std::string &file) {
    std::ifstream fin(file);
    T m;
    fin >> m;
    return m;
}