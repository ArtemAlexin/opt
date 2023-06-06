#include <quasi_newton_methods.h>
#include <unidim_methods.h>

void bfsNextG(CanonicalMatrix &curG, const Vector &deltaX, const Vector &deltaOmega) {
    double rho = (curG * deltaOmega) * deltaOmega;
    auto r = (curG * deltaOmega) / rho - deltaX / (deltaX * deltaOmega);
    curG = curG - sqr(deltaX) / (deltaOmega * deltaX) - sqr(curG * deltaOmega) / rho + rho * sqr(r);
}

void powellNextG(CanonicalMatrix &curG, const Vector &deltaX, const Vector &deltaOmega) {
    auto deltaTildaX = deltaX + curG * deltaOmega;
    curG = curG - sqr(deltaTildaX) / (deltaOmega * deltaTildaX);
}

Vector abstractQuasiNewtonMethod(const Vector &x0,
                                 double eps,
                                 QuasiNewtonMethods::Function &f,
                                 QuasiNewtonMethods::Gradient &grad,
                                 QuasiNewtonMethods::Gessian &H,
                                 const std::function<void(CanonicalMatrix &, const Vector &, const Vector &)> &nextG) {
    size_t dim = x0.size();
    auto I = identityMatrix(dim);

    auto curX = x0;
    auto curOmega = -grad(curX);
    auto curG = I;
    auto curP = curG * curOmega;

    Vector deltaX(dim, std::numeric_limits<double>::infinity());

    while (norm(deltaX) > eps) {
        std::function<double(double)> fun = [&](double alpha) { return f(curX + alpha * curP); };

        double alpha = UnidimMethods::brentsMethod(fun, {-1e9, 1e9}, 1e-7).min;

        auto nextX = curX + alpha * curP;
        auto nextOmega = -grad(nextX);

        deltaX = nextX - curX;
        auto deltaOmega = nextOmega - curOmega;

        nextG(curG, deltaX, deltaOmega);

        curX = nextX;
        curOmega = nextOmega;
        curP = curG * curOmega;
    }

    return curX;
}

Vector abstractQuasiNewtonMethodLogging(const Vector &x0,
                                        double eps,
                                        QuasiNewtonMethods::Function &f,
                                        QuasiNewtonMethods::Gradient &grad,
                                        QuasiNewtonMethods::Gessian &H,
                                        Logging::EvalData &evalData,
                                        const std::function<void(CanonicalMatrix &, const Vector &,
                                                                 const Vector &)> &nextG) {
    size_t dim = x0.size();
    auto I = identityMatrix(dim);

    auto curX = x0;
    auto curOmega = -grad(curX);
    auto curG = I;
    auto curP = curG * curOmega;

    Vector deltaX(dim, std::numeric_limits<double>::infinity());

    evalData.push_back(curX);

    while (norm(deltaX) > eps) {
        std::function<double(double)> fun = [&](double alpha) { return f(curX + alpha * curP); };

        double alpha = UnidimMethods::brentsMethod(fun, {-1e9, 1e9}, 1e-7).min;

        auto nextX = curX + alpha * curP;
        auto nextOmega = -grad(nextX);

        deltaX = nextX - curX;
        auto deltaOmega = nextOmega - curOmega;

        nextG(curG, deltaX, deltaOmega);

        curX = nextX;
        curOmega = nextOmega;
        curP = curG * curOmega;

        evalData.push_back(curX);
    }

    return curX;
}

Vector
QuasiNewtonMethods::bfs(const Vector &x0, double eps, QuasiNewtonMethods::Function &f,
                        QuasiNewtonMethods::Gradient &grad,
                        QuasiNewtonMethods::Gessian &H) {
    return abstractQuasiNewtonMethod(x0, eps, f, grad, H, bfsNextG);
}

Vector
QuasiNewtonMethods::powell(const Vector &x0, double eps, QuasiNewtonMethods::Function &f,
                           QuasiNewtonMethods::Gradient &grad,
                           QuasiNewtonMethods::Gessian &H) {
    return abstractQuasiNewtonMethod(x0, eps, f, grad, H, powellNextG);
}

Vector QuasiNewtonMethods::bfsLogging(const Vector &x0, double eps, QuasiNewtonMethods::Function &f,
                                      QuasiNewtonMethods::Gradient &grad, QuasiNewtonMethods::Gessian &H,
                                      Logging::EvalData &evalData) {
    return abstractQuasiNewtonMethodLogging(x0, eps, f, grad, H, evalData, bfsNextG);
}

Vector QuasiNewtonMethods::powellLogging(const Vector &x0, double eps, QuasiNewtonMethods::Function &f,
                                         QuasiNewtonMethods::Gradient &grad, QuasiNewtonMethods::Gessian &H,
                                         Logging::EvalData &evalData) {
    return abstractQuasiNewtonMethodLogging(x0, eps, f, grad, H, evalData, powellNextG);
}
