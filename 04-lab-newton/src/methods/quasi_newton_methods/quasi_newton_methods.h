#pragma once

#include <functional>

#include <CanonicalMatrix.h>
#include <Vector.h>
#include <logging.h>

namespace QuasiNewtonMethods {

    using Function = std::function<double(const Vector&)>;
    using Gradient = std::function<Vector(const Vector&)>;
    using Gessian = std::function<CanonicalMatrix(const Vector&)>;

    using QuasiNewtonMethod = std::function<Vector(const Vector&, double, Function&, Gradient&, Gessian&)>;

    Vector bfs(const Vector& x0, double eps, Function &f, Gradient &grad, Gessian &H);

    Vector powell(const Vector& x0, double eps, Function &f, Gradient &grad, Gessian &H);

    // Logging methods

    Vector bfsLogging(const Vector& x0, double eps, Function &f, Gradient &grad, Gessian &H, Logging::EvalData& evalData);

    Vector powellLogging(const Vector& x0, double eps, Function &f, Gradient &grad, Gessian &H, Logging::EvalData& evalData);
}