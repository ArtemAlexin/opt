#pragma once

#include <functional>
#include <Vector.h>
#include <CanonicalMatrix.h>
#include <logging.h>

namespace NewtonMethods {

    struct CorsData {
        const Vector ans;
        const std::vector<double> alphas;
        const int iterations;

        CorsData(const Vector &ans, const std::vector<double> &alphas, int iterations)
                : ans(ans), alphas(ans), iterations(iterations) {};
    };

    using Function = std::function<double(const Vector &)>;
    using Gradient = std::function<Vector(const Vector &)>;
    using Gessian = std::function<CanonicalMatrix(const Vector &)>;

    using NewtonMethod = std::function<Vector(const Vector &, double, const Function &, const Gradient &,
                                              const Gessian &)>;

    CorsData classicNewton(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H);

    CorsData
    unidimSearchNewton(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H);

    CorsData
    descentDirectionNewton(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H);

    //  TODO: там нужно два варианта, Артем распарсит и назовет их нормально
    Vector markwardt1(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H);

    Vector markwardt2(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H);

    // Logging methods

    Vector classicNewtonLog(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H, Logging::EvalData&);

    Vector unidimSearchNewtonLog(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H, Logging::EvalData&);

    Vector descentDirectionNewtonLog(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H, Logging::EvalData&);
}
