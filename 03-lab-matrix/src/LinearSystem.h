#pragma once

#include "matrix/Vector.h"
#include "matrix/ProfileMatrix.h"
#include "matrix/LUMatrix.h"
#include "matrix/SparseMatrix.h"

struct EvalData {
    size_t iterationsNumber = 0;

    // add something else if you want
};

inline std::istream &operator>>(std::istream &in, EvalData &v) {
    in >> v.iterationsNumber;
    return in;
}

inline std::ostream &operator<<(std::ostream &out, EvalData &v) {
    out << v.iterationsNumber;
    return out;
}

Vector solveLUGauss(Matrix &A, Vector &b);

void solveLUGauss(const std::string &fileA, const std::string &fileB, const std::string &fileRes);

Vector solveLUGauss2(Matrix &A, Vector &b);

Vector solveLeadingElementGauss(Matrix &A, Vector &b);

void solveLeadingElementGauss(const std::string &fileA, const std::string &fileB, const std::string &fileRes);

Vector solveConjGrad(const Matrix &A, Vector &b, Vector &x0, double eps);

Vector solveConjGradLogging(const Matrix &A, Vector &b, Vector &x0, double eps, EvalData &data);

void solveConjGrad(const std::string &fileA,
                   const std::string &fileB,
                   const std::string &fileRes,
                   const std::string &fileData,
                   Vector &x0, double eps);
