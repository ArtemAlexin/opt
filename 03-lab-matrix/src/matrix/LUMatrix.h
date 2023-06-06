#include <utility>

#include "ProfileMatrix.h"

#pragma once

struct LUMatrix {
    Matrix *matrix;

    LUMatrix() = delete;
    explicit LUMatrix(Matrix &matrix) : matrix(&matrix) {};

    double getL(size_t i, size_t j) const {
        return j > i ? 0 : matrix->get(i, j);
    }

    double getU(size_t i, size_t j) const {
        return i == j ? 1 : (i > j ? 0 : matrix->get(i, j));
    }

    void setL(size_t i, size_t j, double value) {
        assert(j > i);
        matrix->set(i, j, value);
    }

    void setU(size_t i, size_t j, double value) {
        assert(i > j);
        matrix->set(i, j, value);
    }

    size_t size() const {
        return matrix->size();
    }
};

/**
 * Calculates LU decomposition of Matrix m in place.
 * Function doesn't allocate any memory.
 *
 * @param m Matrix to be decomposed
 * @return reference to m
 */
inline LUMatrix toLU(Matrix &m) {
    for (int i = 1; i < m.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            //  calc L[i][j]
            for (int k = 0; k < j; ++k) {
                m.set(i, j, m.get(i, j) - m.get(i, k) * m.get(k, j));
            }
        }
        for (int j = 0; j < i; ++j) {
            //  calc U[j][i]
            for (int k = 0; k < j; ++k) {
                m.set(j, i, m.get(j, i) - m.get(j, k) * m.get(k, i));
            }
            m.set(j, i, m.get(j, i) / m.get(j, j));
        }
        //  calc L[i][i]
        for (int k = 0; k < i; ++k) {
            m.set(i, i, m.get(i, i) - m.get(i, k) * m.get(k, i));
        }
    }
    return LUMatrix(m);
}
