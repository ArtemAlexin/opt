#pragma once

#include <functional>

#include <CanonicalMatrix.h>
#include <Vector.h>

using Function = std::function<double(const Vector &)>;
using Gradient = std::function<Vector(const Vector &)>;
using Gessian = std::function<CanonicalMatrix(const Vector &)>;

struct QuadFunction {

    QuadFunction() : QuadFunction(std::vector<std::vector<double>>({{1, 0}, {0, 1}}), {0, 0}, 0) {}

    QuadFunction(const CanonicalMatrix &A, const Vector &b, double c)
            : A(A),
              b(b),
              c(c),
              function([&](const Vector &x) { return 0.5 * ((this->A * x) * x) + this->b * x + this->c; }),
              gradient([&](const Vector &x) { return this->A * x; }),
              gessian([&](const Vector &x) { return this->A; }) {}

    CanonicalMatrix A;
    Vector b;
    double c;

    Function function;
    Gradient gradient;
    Gessian gessian;
};

const QuadFunction f1(std::vector<std::vector<double>>({{100, 0}, {0, 10}}), {0, 0}, 0);