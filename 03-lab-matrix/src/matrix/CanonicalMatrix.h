#pragma once

#include <vector>
#include <cassert>
#include <cmath>

#include "Matrix.h"
#include "Vector.h"


/** std::vector<std::vector<double>> wrapper implementing Matrix interface */
struct CanonicalMatrix : Matrix {
    CanonicalMatrix(const std::vector<std::vector<double>> &data) : data(data) {}

    CanonicalMatrix(std::vector<std::vector<double>> &&data) : data(data) {}

    CanonicalMatrix(size_t n, Vector &&line) : data(n, line) {}

    double get(size_t i, size_t j) const override {
        return data[i][j];
    }

    void set(size_t i, size_t j, double value) override {
        data[i][j] = value;
    }

    Vector operator*(const Vector &v) const override {
        Vector result(size());
        for (size_t i = 0; i < size(); ++i) {
            for (size_t j = 0; j < v.size(); ++j) {
                result[i] += get(i, j) * v[j];
            }
        }
        return result;
    }

    size_t size() const override {
        return data.size();
    }
private:
    std::vector<std::vector<double>> data;
};

template<typename MatrixType>
CanonicalMatrix toCanonicalMatrix(const MatrixType &m) {
    std::vector<std::vector<double>> m1(m.size(), std::vector<double>(m.size()));
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m.size(); ++j) {
            m1[i][j] = m.get(i, j);
        }
    }
    return m1;
}

/**
 * Returns Euclidean norm of matrix <code>m</code>.
 * @param m
 * @return Euclidean norm of matrix <code>m</code>.
 */
inline double norm(const CanonicalMatrix &m) {
    double norm = 0;
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m.size(); ++j) {
            norm = pow(m.get(i, j), 2);
        }
    }
    return sqrt(norm);
}

/**
 * Returns <code>||v||</code> - Euclidean norm of vector
 *
 * @param v vector
 * @return Euclidean norm of vector
 */
inline double norm(const Vector &v) {
    double norm = 0;
    for (const double x : v) {
        norm += x * x;
    }
    return sqrt(norm);
}

/**
 * Returns scalar production of <code>v1</code> and <code>v2</code>
 *
 * @param v1 first vector
 * @param v2 second vector
 * @return scalar production of <code>v1</code> and <code>v2</code>
 */
inline double operator*(const Vector &v1, const Vector &v2) {
    assert(v1.size() == v2.size());
    double result = 0;
    for (size_t i = 0; i < v1.size(); ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

/**
* Returns product of scalar <code>a</code> and vector <code>v</code>
*
* @param a scalar
* @param v vector
* @return resulting product of scalar <code>a</code> and vector <code>v</code>
*/
inline CanonicalMatrix operator*(double a, const CanonicalMatrix &m) {
    std::vector<std::vector<double>> result(m.size(), Vector(m.size()));
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m.size(); ++j) {
            result[i][j] = a * m.get(i, j);
        }
    }
    return result;
}

/**
 * Returns product of scalar <code>a</code> and vector <code>v</code>
 *
 * @param a scalar
 * @param v vector
 * @return resulting product of scalar <code>a</code> and vector <code>v</code>
 */
inline Vector operator*(double a, const Vector &v) {
    Vector result(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = a * v[i];
    }
    return result;
}

/**
 * Returns sum of two vectors <code>v1</code> and <code>v2</code>
 *
 * @param v1 first vector
 * @param v2 second vector
 * @return sum of two vectors <code>v1</code> and <code>v2</code>
 */
inline Vector operator+(const Vector &v1, const Vector &v2) {
    assert(v1.size() == v2.size());
    Vector result = Vector(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

/**
 * Returns subtraction of two vectors <code>v1</code> and <code>v2</code>
 *
 * @param v1 first vector
 * @param v2 second vector
 * @return subtraction of two vectors <code>v1</code> and <code>v2</code>
 */
inline Vector operator-(const Vector &v1, const Vector &v2) {
    return v1 + (-1.0 * v2);
}


inline Vector operator-(const Vector &v) {
    return -1.0 * v;
}

inline CanonicalMatrix operator-(const CanonicalMatrix &v) {
    return -1.0 * v;
}


