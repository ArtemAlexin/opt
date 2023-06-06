#pragma once

#include <filesystem>
#include "ProfileMatrix.h"
#include "SparseMatrix.h"

using data_t = std::vector<std::vector<double>>;

data_t randomData(size_t n);

data_t randomSymData(size_t n);

data_t randomDiagPosData(size_t n);

// Seq

data_t randomRawSeqData(size_t n);

data_t randomRawSymSeqData(size_t n);

data_t addDominance(data_t data, size_t k);

data_t invSeq(data_t &&data);

// Gilebert

data_t randomGilData(size_t n);

// Vectors

Vector randomVector(size_t n, int radius = 10);

Vector fromSolution(const data_t &data, const Vector &x);

// I/O

template<typename T>
inline void writeTo(const std::string &dir, const std::string &filename, T t) {
    std::filesystem::create_directories(dir);
    std::ofstream fout(dir + "/" + filename);
    fout << t;
}
