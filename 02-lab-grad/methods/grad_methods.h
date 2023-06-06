#pragma once

#include <functional>
#include "matrix.h"
#include "undim_methods/undim_methods.h"

namespace grad_methods {
    struct quad_function {
        double calc(const vector_t &x) const {
            return 0.5 * ((A * x) * x) + B * x + C;
        }

        vector_t grad(const vector_t &x) const {
            return A * x + B;
        }

//        double GCC_K;

        matrix_t A;
        vector_t B;
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

    using eval_data = std::vector<vector_t>;

    using method = std::function<eval_data(const quad_function &, const vector_t&, double, const undim_methods::method_t &)>;

    eval_data grad_descent(const quad_function &f,
                           const vector_t &x0,
                           double eps,
                           const undim_methods::method_t &undim_method = nullptr);

    eval_data quick_grad_descent(const quad_function &alpha_val,
                                 const vector_t &x0,
                                 double eps,
                                 const undim_methods::method_t &undim_method = undim_methods::golden_section_method);

    eval_data conjugate_grad(const quad_function &f,
                             const vector_t &x0,
                             double eps,
                             const undim_methods::method_t &undim_method = nullptr);
}