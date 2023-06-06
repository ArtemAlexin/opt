#include "grad_methods.h"

double calc_f(const grad_methods::quad_function &f, const vector_t &x) {
    return 0.5 * ((f.A * x) * x) + f.B * x + f.C;
}

vector_t grad_f(const grad_methods::quad_function &f, const vector_t &x) {
    return f.A * x + f.B;
}

double calc_alpha(const matrix_t &m) {
    double min_value = m[0][0];
    double max_value = m[0][0];
    for (int i = 1; i < m.size(); ++i) {
        min_value = std::min(min_value, m[i][i]);
        max_value = std::max(max_value, m[i][i]);
    }
    return (min_value / max_value) / 2;
}

grad_methods::eval_data grad_methods::grad_descent(const grad_methods::quad_function &f,
                                                   const vector_t &x0,
                                                   double eps,
                                                   const undim_methods::method_t &undim_method) {
    eval_data data;
    double alpha = calc_alpha(f.A);
    vector_t x = x0; // n-dim zero
    vector_t grad;
    double fx = calc_f(f, x);
    data.push_back(x);
    while (norm(grad = grad_f(f, x)) >= eps) {
        double fy;
        do {
            const vector_t y = x - alpha * grad;
            fy = calc_f(f, y);
            if (fy < fx) {
                x = y;
                fx = fy;
            } else {
                alpha /= 2;
            }
        } while (fy != fx);
        data.push_back(x);
    }
    return data;
}

grad_methods::eval_data grad_methods::quick_grad_descent(const grad_methods::quad_function &f,
                                                         const vector_t &x0,
                                                         double eps,
                                                         const undim_methods::method_t &undim_method) {
    eval_data data;
    double alpha = calc_alpha(f.A);
    vector_t x = x0;
    vector_t grad;
    double fx = calc_f(f, x);
    data.push_back(x);
    while (norm(grad = grad_f(f, x)) >= eps) {
        std::function<double(double)> f_alpha = [&](double alpha_val)
                { return calc_f(f, x - alpha_val * grad); };
        alpha = undim_method(f_alpha, {1e-10, 10000}, 0.0001).min;
        x = x - alpha * grad;
        data.push_back(x);
    }
    return data;
}

#define SQR(val) ((val) * (val))

grad_methods::eval_data grad_methods::conjugate_grad(const grad_methods::quad_function &f,
                                                     const vector_t &x0,
                                                     double eps,
                                                     const undim_methods::method_t &undim_method) {
    eval_data data;
    vector_t x = x0;
    vector_t grad = grad_f(f, x);
    vector_t p = -grad;
    data.push_back(x);
    while (norm(grad) >= eps) {
        const double norm_grad_x = norm(grad);
        const double alpha = SQR(norm_grad_x) / ((f.A * p) * p);
        const vector_t y = x + alpha * p;
        const vector_t gedit = grad + alpha * (f.A * p);
        const double norm_grad_y = norm(gedit);
        const double beta = SQR(norm_grad_y) / SQR(norm_grad_x);
        p = -gedit + beta * p;
        x = y;
        grad = grad_f(f, x);
        data.push_back(x);
    }
    return data;
}