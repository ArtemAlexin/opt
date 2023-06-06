#pragma once

#include <filesystem>
#include <vector>
#include <random>
#include <ctime>

#include "matrix/ProfileMatrix.h"
#include "matrix/SparseMatrix.h"
#include "matrix/Vector.h"

/**
 * Creates an instance of {@code Matrix} and {@code Vector}
 * and writes them to file matrix_t and vector_t,
 * where t is input index
 * Resulting matrix is filled random.
 *
 * @param t input index
*/
inline void generateRandom(size_t t, size_t dim = 0) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    size_t n = dim == 0 ? (gen() % 991) + 10 : dim;
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
    ProfileMatrix m(data);
    std::ofstream fout("../tests/matrix_io/matrix_" + std::to_string(t) + ".txt");
    fout << m;
    Vector b(n);
    for (int i = 0; i < n; ++i) {
        b[i] = static_cast<int>(gen() % 21) - 10;
    }
    std::ofstream fout_v("../tests/vector_io/vector_" + std::to_string(t) + ".txt");
    fout_v << b;
}

/**
 * Creates an instance of {@code Matrix} and {@code Vector}
 * and writes them to file extra_matrix_t and extra_vector_t,
 * where t is input index
 * Resulting matrix is filled random.
 *
 * @param t input index
*/
inline void generateExtraRandom(size_t t, size_t dim = 0) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    size_t n = dim == 0 ? (gen() % 991) + 10 : dim;
    std::vector<std::vector<double>> data(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            data[i][j] = static_cast<int>(gen() % 21) - 10 + ((double) rand() / (double) RAND_MAX);
        }
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            data[i][j] = data[j][i];
        }
    }
    SparseMatrix m(data);
    std::ofstream fout("../tests/matrix_io/extra_matrix_" + std::to_string(t) + ".txt");
    fout << m;
    Vector b(n);
    for (int i = 0; i < n; ++i) {
        b[i] = static_cast<int>(gen() % 21) - 10;
    }
    std::ofstream fout_v("../tests/vector_io/extra_vector_" + std::to_string(t) + ".txt");
    fout_v << b;
}

/**
 * Creates an instance of {@code Matrix} and {@code Vector}
 * and writes them to file matrix_seq_k and vector_seq_k,
 * where k is input index
 *
 * @param k conditionality number (число обусловленности)
 */
inline void generateSequence(size_t k) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    size_t n = (gen() % 991) + 10;
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
        if (i == 0) {
            data[i][i] += pow(0.1, k);
        }
    }
    Vector b(n);
    for (size_t i = 0; i < n; ++i) {
        b[i] = static_cast<double>(i) + 1;
    }
    ProfileMatrix m(data);
    std::ofstream fout("../tests/matrix_io/matrix_seq_" + std::to_string(k) + ".txt");
    fout << m;
    b = m * b;
    std::ofstream fout_v("../tests/vector_io/vector_seq_" + std::to_string(k) + ".txt");
    fout_v << b;
}


/**
 * Creates an instance of {@code Matrix}
 * and writes it to file matrix_gil_k, where k is input index.
 *
 * @param n dimension of a matrix
 */
inline void generateGilbert(size_t n, size_t k) {
    std::vector<std::vector<double>> data(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            data[i][j] = 1.0 / (static_cast<double>(i + j) + 1);
        }
    }
    ProfileMatrix m(data);
    std::ofstream fout("../tests/matrix_io/matrix_gil_" + std::to_string(k) + ".txt");
    fout << m;
    Vector b(n);
    for (int i = 0; i < n; ++i) {
        b[i] = i + 1;
    }
    b = m * b;
    std::ofstream fout_v("../tests/vector_io/vector_gil_" + std::to_string(k) + ".txt");
    fout_v << b;
}


inline Vector generateVectorOfSize(size_t dim) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    Vector v(dim);
    for (int i = 0; i < dim; ++i) {
        v[i] = static_cast<int>(gen() % 21) - 10;
    }
    return v;
}

#define TEST_DIR(dim, testId) ("../tests/bonus/test_" + std::to_string(dim) + "_" + std::to_string(testId))
#define A_FILE(dim, testId) ("../tests/bonus/test_" + std::to_string(dim) + "_" + std::to_string(testId) + "/A"  + ".txt")
#define B_FILE(dim, testId) ("../tests/bonus/test_" + std::to_string(dim) + "_" + std::to_string(testId) + "/b"  + ".txt")
#define X_FILE(dim, testId) ("../tests/bonus/test_" + std::to_string(dim) + "_" + std::to_string(testId) + "/x"  + ".txt")
#define DATA_FILE(dim, testId) ("../tests/bonus/test_" + std::to_string(dim) + "_" + std::to_string(testId) + "/data"  + ".txt")


inline void generateRandomBonus(size_t t, const Vector &x) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    size_t n = x.size();
    std::vector<std::vector<double>> data(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            data[i][j] = static_cast<int>(gen() % 21) - 10 + ((double) rand() / (double) RAND_MAX);
        }
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            data[i][j] = data[j][i];
        }
    }
    SparseMatrix m(data);
    std::filesystem::create_directories(TEST_DIR(n, t));
    std::ofstream fout(A_FILE(n, t));
    fout << m;
    Vector b = m * x;
    std::ofstream fout_v(B_FILE(n, t));
    fout_v << b;
}

#define TEST_DIR_SEQ(dim, testId) ("../tests/bonus/test_seq_" + std::to_string(dim) + "_" + std::to_string(testId))
#define A_FILE_SEQ(dim, testId) ("../tests/bonus/test_seq_" + std::to_string(dim) + "_" + std::to_string(testId) + "/A"  + ".txt")
#define B_FILE_SEQ(dim, testId) ("../tests/bonus/test_seq_" + std::to_string(dim) + "_" + std::to_string(testId) + "/b"  + ".txt")
#define X_FILE_SEQ(dim, testId) ("../tests/bonus/test_seq_" + std::to_string(dim) + "_" + std::to_string(testId) + "/x"  + ".txt")
#define DATA_FILE_SEQ(dim, testId) ("../tests/bonus/test_seq_" + std::to_string(dim) + "_" + std::to_string(testId) + "/data"  + ".txt")

inline void generateBonusSequence(size_t t, const Vector &x) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    size_t n = x.size();
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
        if (i == 0) {
            data[i][i]++;
        }
    }
    SparseMatrix m(data);
    std::filesystem::create_directories(TEST_DIR_SEQ(n, t));
    std::ofstream fout(A_FILE_SEQ(n, t));
    fout << m;
    Vector b = m * x;
    std::ofstream fout_v(B_FILE_SEQ(n, t));
    fout_v << b;
}

#define TEST_DIR_GIL(dim, testId) ("../tests/bonus/test_gil_" + std::to_string(dim) + "_" + std::to_string(testId))
#define A_FILE_GIL(dim, testId) ("../tests/bonus/test_gil_" + std::to_string(dim) + "_" + std::to_string(testId) + "/A"  + ".txt")
#define B_FILE_GIL(dim, testId) ("../tests/bonus/test_gil_" + std::to_string(dim) + "_" + std::to_string(testId) + "/b"  + ".txt")
#define X_FILE_GIL(dim, testId) ("../tests/bonus/test_gil_" + std::to_string(dim) + "_" + std::to_string(testId) + "/x"  + ".txt")
#define DATA_FILE_GIL(dim, testId) ("../tests/bonus/test_gil_" + std::to_string(dim) + "_" + std::to_string(testId) + "/data"  + ".txt")

inline void generateBonusGilbert(size_t t, const Vector &x) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    size_t n = x.size();
    std::vector<std::vector<double>> data(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            data[i][j] = 1.0 / (static_cast<double>(i + j) + 1);
        }
    }
    SparseMatrix m(data);
    std::filesystem::create_directories(TEST_DIR_GIL(n, t));
    std::ofstream fout(A_FILE_GIL(n, t));
    fout << m;
    Vector b = m * x;
    std::ofstream fout_v(B_FILE_GIL(n, t));
    fout_v << b;
}