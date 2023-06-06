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
        Vector result(rowsSize());
        for (size_t i = 0; i < rowsSize(); ++i) {
            for (size_t j = 0; j < v.size(); ++j) {
                result[i] += get(i, j) * v[j];
            }
        }
        return result;
    }

//    CanonicalMatrix operator*(const CanonicalMatrix &other) const {
//        assert(colsSize() == other.rowsSize());
//        std::vector<std::vector<double>> resultData(rowsSize(), std::vector<double>(other.colsSize()));
//        for (size_t i = 0; i < rowsSize(); ++i) {
//            for (size_t j = 0; j < other.colsSize(); ++j) {
//                for (size_t k = 0; k < colsSize(); ++k) {
//                    resultData[i][j] += get(i, k) * other.get(k, j);
//                }
//            }
//        }
//        return resultData;
//    }

    size_t rowsSize() const override {
        return data.size();
    }

    size_t colsSize() const {
        return data[0].size();
    }

private:
    std::vector<std::vector<double>> data;
};

template<typename MatrixType>
CanonicalMatrix toCanonicalMatrix(const MatrixType &m) {
    std::vector<std::vector<double>> m1(m.rowsSize(), std::vector<double>(m.rowsSize()));
    for (int i = 0; i < m.rowsSize(); ++i) {
        for (int j = 0; j < m.rowsSize(); ++j) {
            m1[i][j] = m.get(i, j);
        }
    }
    return m1;
}

inline CanonicalMatrix identityMatrix(size_t sz) {
    std::vector<std::vector<double>> data(sz, std::vector<double>(sz));
    for (size_t i = 0; i < sz; ++i) {
        data[i][i] = 1;
    }
    return data;
}

/**
 * Returns Euclidean norm of matrix <code>m</code>.
 * @param m
 * @return Euclidean norm of matrix <code>m</code>.
 */
inline double norm(const CanonicalMatrix &m) {
    double norm = 0;
    for (size_t i = 0; i < m.rowsSize(); ++i) {
        for (size_t j = 0; j < m.rowsSize(); ++j) {
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


inline CanonicalMatrix operator^(const Vector &v1, const Vector &v2) {
    std::vector<std::vector<double>> data(v1.size(), std::vector<double>(v2.size(), 0));
    for (size_t i = 0; i < v1.size(); ++i) {
        for (size_t j = 0; j < v2.size(); ++j) {
            data[i][j] = v1[i] * v2[j];
        }
    }
    return data;
}

inline CanonicalMatrix sqr(const Vector &v) {
    std::vector<std::vector<double>> data(v.size(), std::vector<double>(v.size(), 0));
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j < v.size(); ++j) {
            data[i][j] = v[i] * v[j];
        }
    }
    return data;
}

inline CanonicalMatrix operator+(const CanonicalMatrix &m1, const CanonicalMatrix &m2) {
    std::vector<std::vector<double>> result(m1.rowsSize(), Vector(m1.rowsSize()));
    for (size_t i = 0; i < m1.rowsSize(); ++i) {
        for (size_t j = 0; j < m1.rowsSize(); ++j) {
            result[i][j] = m1.get(i, j) + m2.get(i, j);
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
inline CanonicalMatrix operator-(const CanonicalMatrix &m1, const CanonicalMatrix &m2) {
    std::vector<std::vector<double>> result(m1.rowsSize(), Vector(m1.rowsSize()));
    for (size_t i = 0; i < m1.rowsSize(); ++i) {
        for (size_t j = 0; j < m1.rowsSize(); ++j) {
            result[i][j] = m1.get(i, j) - m2.get(i, j);
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
inline CanonicalMatrix operator*(double a, const CanonicalMatrix &m) {
    std::vector<std::vector<double>> result(m.rowsSize(), Vector(m.colsSize()));
    for (size_t i = 0; i < m.rowsSize(); ++i) {
        for (size_t j = 0; j < m.rowsSize(); ++j) {
            result[i][j] = a * m.get(i, j);
        }
    }
    return result;
}


inline CanonicalMatrix operator/(const CanonicalMatrix &m, double a) {
    std::vector<std::vector<double>> result(m.rowsSize(), Vector(m.colsSize()));
    for (size_t i = 0; i < m.rowsSize(); ++i) {
        for (size_t j = 0; j < m.colsSize(); ++j) {
            result[i][j] /= a;
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
 * Returns division of vector <code>v</code> and scalar <code>a</code>.
 *
 * @param v vector
 * @param a scalar
 * @return resulting division of vector <code>v</code> and scalar <code>a</code>.
 */
inline Vector operator/(const Vector &v, double a) {
    Vector result(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = v[i] / a;
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


