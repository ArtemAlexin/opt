#pragma once

#include <vector>
#include <cassert>
#include <cmath>

using matrix_t = std::vector<std::vector<double>>;
using vector_t = std::vector<double>;

/**
 * Returns Euclidean norm of matrix <code>m</code>.
 * @param m
 * @return Euclidean norm of matrix <code>m</code>.
 */
inline double norm(const matrix_t &m) {
    double result = 0;
    for (const vector_t &row : m) {
        for (double val : row) {
            result += val * val;
        }
    }
    return sqrt(result);
}

/**
 * Returns <code>||v||</code> - Euclidean norm of vector
 *
 * @param v vector
 * @return Euclidean norm of vector
 */
inline double norm(const vector_t &v) {
    double norm = 0;
    for (const double x : v) {
        norm += x * x;
    }
    return sqrt(norm);
}

/**
 * Returns matrix production of matrix <code>m</code> and vector <code>v</code>.
 *
 * @param m matrix
 * @param v vector
 * @return matrix production of matrix <code>m</code> and vector <code>v</code>.
 */
inline vector_t operator*(const matrix_t &m, const vector_t &v) {
    assert(m[0].size() == v.size());
    vector_t result(m.size());
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < v.size(); ++j) {
            result[i] += m[i][j] * v[j];
        }
    }
    return result;
}

/**
 * Returns scalar production of <code>v1</code> and <code>v2</code>
 *
 * @param v1 first vector
 * @param v2 second vector
 * @return scalar production of <code>v1</code> and <code>v2</code>
 */
inline double operator*(const vector_t &v1, const vector_t &v2) {
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
inline matrix_t operator*(double a, const matrix_t &m) {
    matrix_t result(m.size(), vector_t(m[0].size()));
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m[i].size(); ++j) {
            result[i][j] = a * m[i][j];
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
inline vector_t operator*(double a, const vector_t &v) {
    vector_t result(v.size());
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
inline vector_t operator+(const vector_t &v1, const vector_t &v2) {
    assert(v1.size() == v2.size());
    vector_t result = vector_t(v1.size());
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
inline vector_t operator-(const vector_t &v1, const vector_t &v2) {
    return v1 + (-1.0 * v2);
}


inline vector_t operator-(const vector_t &v) {
    return -1.0 * v;
}

inline matrix_t operator-(const matrix_t &v) {
    return -1.0 * v;
}


