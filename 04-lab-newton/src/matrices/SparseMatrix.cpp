#include <iomanip>
#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(const std::vector<std::vector<double>> &data) : SparseMatrix(data.size()) {
    size_t n = data.size();
    for (size_t i = 0; i < n; ++i) {
        diagonal[i] = data[i][i];
    }
    for (size_t i = 0; i < n; ++i) {
        size_t j = 0;
        while (j < i && data[i][j] == 0) {
            ++j;
        }
        profile[i] = rowElements.size();
        for (; j < i; ++j) {
            if (data[i][j] != 0) {
                rowElements.push_back(data[i][j]);
                colNumber.push_back(j);
            }
        }
    }
    assert(profile[0] == 0);
    assert(n == 0 || profile[1] == 0);
    profile[n] = rowElements.size();
    for (size_t j = 0; j < n; ++j) {
        size_t i = 0;
        while (i < j && data[i][j] == 0) {
            ++i;
        }
        assert(profile[j] == colElements.size());
        for (; i < j; ++i) {
            if (data[i][j] != 0) {
                assert(colNumber[colElements.size()] == i);
                colElements.push_back(data[i][j]);
            }
        }
    }
    assert(profile[n] == colElements.size());
}

size_t binarySearch(const SparseMatrix &m, size_t from, size_t to, size_t j) {
    ssize_t left = static_cast<ssize_t>(from) - 1;
    ssize_t right = static_cast<ssize_t>(to);
    while (left + 1 != right) {
        ssize_t mid = left + (right - left) / 2;
        if (m.colNumber[mid] < j) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return right;
}

void SparseMatrix::resizeAndClear(size_t n) {
    ProfileMatrix::resizeAndClear(n);
    colNumber.clear();
}

double SparseMatrix::get(size_t i, size_t j) const {
    if (i == j) {
        return diagonal[i];
    }
    if (i > j) {
        size_t from = profile[i];
        size_t to = profile[i + 1];
        size_t pos = binarySearch(*this, from, to, j);
        return (from < to && colNumber[pos] == j && pos != to ? rowElements[pos] : 0);
    } else {
        size_t from = profile[j];
        size_t to = profile[j + 1];
        size_t pos = binarySearch(*this, from, to, i);
        return (from < to && colNumber[pos] == i && pos != to ? colElements[pos] : 0);
    }
}

void SparseMatrix::set(size_t i, size_t j, double value) {
    assert(false);
}

Vector SparseMatrix::operator*(const Vector &v) const {
    Vector result(rowsSize());
    for (size_t i = 0; i < rowsSize(); ++i) {
        result[i] += diagonal[i] * v[i];
    }
    for (size_t i = 0; i < rowsSize(); ++i) {
        for (size_t j_ = profile[i]; j_ < profile[i + 1]; ++j_) {
            result[i] += rowElements[j_] * v[colNumber[j_]];
        }
    }
    for (size_t j = 0; j < rowsSize(); ++j) {
        for (size_t i_ = profile[j]; i_ < profile[j + 1]; ++i_) {
            result[colNumber[i_]] += colElements[i_] * v[j];
        }
    }
    return result;
}

std::ifstream &operator>>(std::ifstream &in, SparseMatrix &m) {
    in >> std::fixed >> std::setprecision(10);
    in >> (ProfileMatrix &) m;
    size_t k = m.profile[m.rowsSize()];
    m.colNumber.resize(k);
    for (size_t i = 0; i < k; ++i) {
        in >> m.colNumber[i];
    }
    return in;
}

std::ofstream &operator<<(std::ofstream &out, SparseMatrix &m) {
    out << std::fixed << std::setprecision(10);
    out << (ProfileMatrix &) m;
    size_t k = m.profile[m.rowsSize()];
    for (size_t i = 0; i < k; ++i) {
        out << m.colNumber[i] << ' ';
    }
    out << "\n";
    return out;
}
