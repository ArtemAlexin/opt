#include <iomanip>
#include "ProfileMatrix.h"

ProfileMatrix::ProfileMatrix(const std::vector<std::vector<double>> &data) : ProfileMatrix(data.size()) {
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
            rowElements.push_back(data[i][j]);
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
            colElements.push_back(data[i][j]);
        }
    }
    assert(profile[n] == colElements.size());
}

void ProfileMatrix::resizeAndClear(size_t n) {
    diagonal.clear();
    diagonal.resize(n);
    rowElements.clear();
    colElements.clear();
    profile.clear();
    profile.resize(n + 1);
}

void ProfileMatrix::set(size_t i, size_t j, double value) {
    if (i == j) {
        diagonal[i] = value;
        return;
    }
    if (i > j) {
        size_t profileSize = profile[i + 1] - profile[i];
        size_t profileBegin = i - profileSize;
        assert(j >= profileBegin || value == 0 || value != value);
        if (j >= profileBegin && value == value) {
            rowElements[profile[i] + (j - profileBegin)] = value;
        }
    } else {
        size_t profileSize = profile[j + 1] - profile[j];
        size_t profileBegin = j - profileSize;
        assert(i >= profileBegin || value == 0 || value != value);
        if (i >= profileBegin && value == value) {
            colElements[profile[j] + (i - profileBegin)] = value;
        }
    }
}

double ProfileMatrix::get(size_t i, size_t j) const {
    if (i == j) {
        return diagonal[i];
    }
    if (i > j) {
        size_t profileSize = profile[i + 1] - profile[i];
        size_t profileBegin = i - profileSize;
        return (j < profileBegin ? 0 : rowElements[profile[i] + (j - profileBegin)]);
    } else {
        size_t profileSize = profile[j + 1] - profile[j];
        size_t profileBegin = j - profileSize;
        return (i < profileBegin ? 0 : colElements[profile[j] + (i - profileBegin)]);
    }
}

Vector ProfileMatrix::operator*(const Vector &v) const  {
    Vector result(size());
    for (size_t i = 0; i < size(); ++i) {
        result[i] += diagonal[i] * v[i];
    }
    for (size_t i = 0; i < size(); ++i) {
        size_t profileSize = profile[i + 1] - profile[i];
        for (size_t j = profile[i]; j < profile[i + 1]; ++j) {
            result[i] += rowElements[j] * v[j - profile[i] + i - profileSize];
        }
    }
    for (size_t j = 0; j < size(); ++j) {
        size_t profileSize = profile[j + 1] - profile[j];
        for (size_t i = profile[j]; i < profile[j + 1]; ++i) {
            result[i - profile[j] + j - profileSize] += colElements[i] * v[j];
        }
    }
    return result;
}

std::istream &operator>>(std::istream &in, ProfileMatrix &m) {
    size_t n;
    in >> std::fixed >> std::setprecision(10) >> n;  //  dimension of matrix
    assert(n >= 0);
    m.resizeAndClear(n);
    for (size_t i = 0; i < n; ++i) {
        in >> m.diagonal[i];
    }
    for (size_t i = 0; i <= n; ++i) {
        in >> m.profile[i];
    }
    assert(m.profile[0] == 0);
    assert(n == 0 || m.profile[1] == 0);
    size_t k = m.profile[n];  //  size of row and col arrays
    m.rowElements.resize(k);
    for (size_t i = 0; i < k; ++i) {
        in >> m.rowElements[i];
    }
    m.colElements.resize(k);
    for (size_t i = 0; i < k; ++i) {
        in >> m.colElements[i];
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, ProfileMatrix &m) {
    size_t n = m.size();
    out << std::fixed << std::setprecision(10) << n << "\n";  //  dimension of matrix
    assert(n >= 0);
    for (size_t i = 0; i < n; ++i) {
        out << m.diagonal[i] << ' ';
    }
    out << "\n";
    for (size_t i = 0; i <= n; ++i) {
        out << m.profile[i] << ' ';
    }
    out << "\n";
    size_t k = m.profile[n];  //  size of row and col arrays
    for (size_t i = 0; i < k; ++i) {
        out << m.rowElements[i] << ' ';
    }
    out << "\n";
    for (size_t i = 0; i < k; ++i) {
        out << m.colElements[i] << ' ';
    }
    out << "\n";
    return out;
}
