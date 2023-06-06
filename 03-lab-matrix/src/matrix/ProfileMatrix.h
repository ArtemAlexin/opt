#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>

#include "CanonicalMatrix.h"

struct ProfileMatrix : Matrix {
    ProfileMatrix() = default;

    explicit ProfileMatrix(size_t n)
            : diagonal(n),
              rowElements(0),
              colElements(0),
              profile(n + 1) {};

    ProfileMatrix(const std::vector<std::vector<double>> &data);

    virtual void resizeAndClear(size_t n);

    double get(size_t i, size_t j) const override;

    void set(size_t i, size_t j, double value) override;

    size_t size() const override {
        return diagonal.size();
    }

    Vector operator*(const Vector &v) const override;

// protected:
    std::vector<double> diagonal;
    std::vector<double> rowElements;
    std::vector<double> colElements;
    std::vector<size_t> profile;

    friend std::istream &operator>>(std::istream &, ProfileMatrix &);
    friend std::ostream &operator<<(std::ostream &, ProfileMatrix &);
//    friend Vector operator*(const ProfileMatrix &m, const Vector &v);
};

std::istream &operator>>(std::istream &in, ProfileMatrix &m);

std::ostream &operator<<(std::ostream &out, ProfileMatrix &m);
