#include <unidim_methods.h>
#include <newton_methods.h>
#include <LinearSystem.h>


namespace NewtonMethods {

    //  работает очень плохо, сходится в очень маленькой окрестности решения
    CorsData classicNewton(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H) {
        Vector x_prev;
        Vector cx0 = x0;
        Vector x_curr = x0;
        Vector p;
        std::vector<double> alphas;
        int it = 0;
        do {
            x_prev = x_curr;
            CanonicalMatrix matrix = H(x_prev);
            Vector b = -grad(x_prev);
            p = solveConjGrad(matrix, b, cx0, 1e-6);
            x_curr = x_prev + p;
            ++it;
        } while (norm(x_curr - x_prev) > eps && norm(p) > eps && it < 1e4);
        return CorsData(x_curr, alphas, it);
    }

    CorsData unidimSearchNewton(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H) {
        Vector x_prev;
        Vector x_curr = x0;
        Vector cx0 = x0;
        Vector p;
        std::vector<double> alphas;
        int it = 0;
        do {
            x_prev = x_curr;
            CanonicalMatrix matrix = H(x_prev);
            Vector b = -grad(x_prev);
            p = solveConjGrad(matrix, b, cx0, 1e-6);
            UnidimMethods::UndimFunction uf = [&f, x_prev, &p](double a) {
                Vector x = x_prev + a * p;
                return f(x);
            };
            UnidimMethods::EvalData data = UnidimMethods::goldenSectionMethod(uf, {-10000, 10000}, 1e-6);
            double alpha = data.min;
            alphas.push_back(alpha);
            x_curr = x_prev + alpha * p;
            ++it;
        } while (norm(x_curr - x_prev) > eps && norm(p) > eps && it < 1e4);
        return CorsData(x_curr, alphas, it);
    }

    CorsData descentDirectionNewton(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H) {
        Vector x_prev;
        Vector x_curr = x0;
        Vector cx0 = x0;
        Vector p;
        std::vector<double> alphas;
        int it = 0;
        do {
            x_prev = x_curr;
            CanonicalMatrix matrix = H(x_prev);
            Vector b = -grad(x_prev);
            p = solveConjGrad(matrix, b, cx0, 1e-6);
            if (p * b < 0) {
                p = b;
            }
            UnidimMethods::UndimFunction uf = [&f, x_prev, &p](double a) {
                Vector x = x_prev + a * p;
                return f(x);
            };
            UnidimMethods::EvalData data = UnidimMethods::brentsMethod(uf, {-10000, 10000}, 1e-6);
            double alpha = data.min;
            alphas.push_back(alpha);
            x_curr = x_prev + alpha * p;
            ++it;
        } while (norm(x_curr - x_prev) > eps && norm(p) > eps && it < 1e4);
        return CorsData(x_curr, alphas, it);
    }

    //  TODO: там нужно два варианта, Артем распарсит и назовет их нормально
    Vector markwardt1(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H) {
        return {};
    }

    Vector markwardt2(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H) {
        return {};
    }



    // Logging methods

    Vector classicNewtonLog(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H,
                            Logging::EvalData &evalData) {
        Vector x_prev;
        Vector x_curr = x0;
        Vector p;
        int i = 0;
        evalData.push_back(x_curr);
        do {
            x_prev = x_curr;
            CanonicalMatrix matrix = H(x_prev);
            Vector b = -grad(x_prev);
            p = solveLUGauss(matrix, b);
            x_curr = x_prev + p;
            ++i;
            evalData.push_back(x_curr);
        } while (norm(x_curr - x_prev) > eps && norm(p) > eps && i < 1e4);
        return x_curr;
    }

    Vector
    unidimSearchNewtonLog(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H,
                          Logging::EvalData &evalData) {
        Vector x_prev;
        Vector x_curr = x0;
        Vector p;
        int i = 0;
        evalData.push_back(x_curr);
        do {
            x_prev = x_curr;
            CanonicalMatrix matrix = H(x_prev);
            Vector b = -grad(x_prev);
            p = solveLUGauss(matrix, b);
            UnidimMethods::UndimFunction uf = [&f, x_prev, &p](double a) {
                Vector x = x_prev + a * p;
                return f(x);
            };
            UnidimMethods::EvalData data = UnidimMethods::goldenSectionMethod(uf, {-10000, 10000}, 1e-6);
            double alpha = data.min;
            x_curr = x_prev + alpha * p;
            ++i;
            evalData.push_back(x_curr);
        } while (norm(x_curr - x_prev) > eps && norm(p) > eps && i < 1e4);
        return x_curr;
    }

    Vector
    descentDirectionNewtonLog(const Vector &x0, double eps, const Function &f, const Gradient &grad, const Gessian &H,
                              Logging::EvalData &evalData) {
        Vector x_prev;
        Vector x_curr = x0;
        Vector p;
        int i = 0;
        evalData.push_back(x_curr);
        do {
            x_prev = x_curr;
            CanonicalMatrix matrix = H(x_prev);
            Vector b = -grad(x_prev);
            p = solveLUGauss(matrix, b);
            if (p * b < 0) {
                p = b;
            }
            UnidimMethods::UndimFunction uf = [&f, x_prev, &p](double a) {
                Vector x = x_prev + a * p;
                return f(x);
            };
            UnidimMethods::EvalData data = UnidimMethods::brentsMethod(uf, {-10000, 10000}, 1e-6);
            double alpha = data.min;
            x_curr = x_prev + alpha * p;
            ++i;
            evalData.push_back(x_curr);
        } while (norm(x_curr - x_prev) > eps && norm(p) > eps && i < 1e4);
        return x_curr;
    }
}