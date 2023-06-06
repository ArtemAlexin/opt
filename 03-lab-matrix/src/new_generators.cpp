#include "new_generators.h"
#include <random>


std::vector<std::vector<double>> randomData(size_t n) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::vector<std::vector<double>> data(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            data[i][j] = static_cast<int>(gen() % 21) - 10 + ((double) rand() / (double) RAND_MAX);
        }
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            if (data[j][i] == 0) {
                data[i][j] = 0;
            } else {
                data[i][j] = static_cast<int>(gen() % 21) - 10 + ((double) rand() / (double) RAND_MAX);
                if (data[i][j] == 0) {
                    data[i][j] = ((gen() % 2) ? data[j][i] : -data[j][i]) + ((double) rand() / (double) RAND_MAX);
                }
            }
        }
    }
    return data;
}

data_t randomSymData(size_t n) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::vector<std::vector<double>> data(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            data[i][j] = static_cast<int>(gen() % 5) - 2 + ((double) rand() / (double) RAND_MAX);
        }
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            data[i][j] = data[j][i];
        }
    }
    return data;
}

data_t randomRawSeqData(size_t n) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::vector<std::vector<double>> data(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            data[i][j] = static_cast<int>(gen() % 5) - 4;
        }
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            if (data[j][i] == 0) {
                data[i][j] = 0;
            } else {
                data[i][j] = static_cast<int>(gen() % 5) - 4;
                if (data[i][j] == 0) {
                    data[i][j] = data[j][i];
                }
            }
        }
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                data[i][i] -= data[i][j];
            }
        }
    }
    return data;
}

data_t randomRawSymSeqData(size_t n) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::vector<std::vector<double>> data(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            data[i][j] = static_cast<int>(gen() % 5) - 4;
        }
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            data[i][j] = data[j][i];
        }
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                data[i][i] -= data[i][j];
            }
        }
    }
    return data;
}

data_t addDominance(data_t data, size_t k) {
    data[0][0] += pow(0.1, static_cast<double>(k));
    return data;
}

data_t invSeq(data_t &&data) {
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            data[i][j] = -data[i][j];
            data[j][i] = -data[j][i];
        }
    }
    return data;
}

std::vector<std::vector<double>> randomGilData(size_t n) {
    std::vector<std::vector<double>> data(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            data[i][j] = 1.0 / (static_cast<double>(i + j) + 1);
        }
    }
    return data;
}

Vector randomVector(size_t n) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    Vector v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = static_cast<int>(gen() % 21) - 10;
    }
    return v;
}

Vector fromSolution(const std::vector<std::vector<double>> &data, const Vector &x) {
    return CanonicalMatrix(data) * x;
}
