#pragma once

#include <iostream>
#include <fstream>
#include "CanonicalMatrix.h"
#include "ProfileMatrix.h"

struct SparseMatrix : ProfileMatrix {
    SparseMatrix() = default;

    SparseMatrix(size_t n) : ProfileMatrix(n), colNumber() {}

    SparseMatrix(const std::vector<std::vector<double>> &data);

    void resizeAndClear(size_t n) override;

    double get(size_t i, size_t j) const override;

    // unsupported method
    void set(size_t i, size_t j, double value) override;

    Vector operator*(const Vector &v) const override;

    friend std::ifstream &operator>>(std::ifstream &in, SparseMatrix& m);
    friend std::ofstream &operator<<(std::ofstream &out, SparseMatrix& m);

// protected:
    std::vector<size_t> colNumber;
};

std::ifstream &operator>>(std::ifstream &in, SparseMatrix &m);

std::ofstream &operator<<(std::ofstream &out, SparseMatrix &m);
