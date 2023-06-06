#pragma once

#include <functional>

#include <unidim_methods.h>

#include <Matrix.h>
#include <Vector.h>
#include <CanonicalMatrix.h>

namespace GradMethods {
    struct QuadFunction {
        double calc(const Vector &x) const {
            return 0.5 * (((*A) * x) * x) + B * x + C;
        }

        Vector grad(const Vector &x) const {
            return (*A) * x + B;
        }

        Matrix *A;
        Vector B;
        double C;
    };

//    struct point {
//        vector_t x;
//        double fx;
//    };
//
//    struct iteration {
//        point current_point; // (x, f(x))
//        vector_t p;
//        std::vector<point> approximations; // [(x + alpha * p, f(x + alpha * p))]
//    };
//
//    struct eval_data {
//        void next_point(const point &current_point, const vector_t &p) {
//            iterations.push_back({current_point, p, {}});
//        }
//
//        void add_approximation(const point &approximating_point) {
//            iterations.back().approximations.push_back(approximating_point);
//        }
//
//        std::vector<iteration> iterations;
//    };

    using EvalData = std::vector<Vector>;

    using GradMethod = std::function<EvalData(const QuadFunction &, const Vector &, double, const UndimMethods::UndimMethod &)>;

    EvalData gradDescent(const QuadFunction &f,
                         const Vector &x0,
                         double eps,
                         const UndimMethods::UndimMethod &undim_method = nullptr);

    EvalData quickGradDescent(const QuadFunction &f,
                              const Vector &x0,
                              double eps,
                              const UndimMethods::UndimMethod &undim_method = UndimMethods::goldenSectionMethod);

    EvalData conjGrad(const QuadFunction &f,
                      const Vector &x0,
                      double eps,
                      const UndimMethods::UndimMethod &undim_method = nullptr);
}
