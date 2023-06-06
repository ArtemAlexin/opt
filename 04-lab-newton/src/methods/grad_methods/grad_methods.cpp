#include "grad_methods.h"

double calcF(const GradMethods::QuadFunction &f, const Vector &x) {
    return 0.5 * (((*f.A) * x) * x) + f.B * x + f.C;
}

Vector gradF(const GradMethods::QuadFunction &f, const Vector &x) {
    return (*f.A) * x + f.B;
}

double calcAlpha(const Matrix *m) {
//    double min_value = m[0][0];
//    double max_value = m[0][0];
//    for (int i = 1; i < m.size(); ++i) {
//        min_value = std::min(min_value, m[i][i]);
//        max_value = std::max(max_value, m[i][i]);
//    }
    double min_value = m->get(0, 0);
    double max_value = m->get(0, 0);
    for (int i = 1; i < m->size(); ++i) {
        min_value = std::min(min_value, m->get(i, i));
        max_value = std::max(max_value, m->get(i, i));
    }
    return (min_value / max_value) / 2;
}

GradMethods::EvalData GradMethods::gradDescent(const GradMethods::QuadFunction &f,
                                               const Vector &x0,
                                               double eps,
                                               const UndimMethods::UndimMethod &undim_method) {
    EvalData data;
    double alpha = calcAlpha(f.A);
    Vector x = x0; // n-dim zero
    Vector grad;
    double fx = calcF(f, x);
    data.push_back(x);
    while (norm(grad = gradF(f, x)) >= eps) {
        double fy;
        do {
            const Vector y = x - alpha * grad;
            fy = calcF(f, y);
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

GradMethods::EvalData GradMethods::quickGradDescent(const GradMethods::QuadFunction &f,
                                                    const Vector &x0,
                                                    double eps,
                                                    const UndimMethods::UndimMethod &undim_method) {
    EvalData data;
    double alpha = calcAlpha(f.A);
    Vector x = x0;
    Vector grad;
    double fx = calcF(f, x);
    data.push_back(x);
    while (norm(grad = gradF(f, x)) >= eps) {
        std::function<double(double)> f_alpha = [&](double alpha_val)
                { return calcF(f, x - alpha_val * grad); };
        alpha = undim_method(f_alpha, {1e-10, 10000}, 0.0001).min;
        x = x - alpha * grad;
        data.push_back(x);
    }
    return data;
}

#define SQR(val) ((val) * (val))

GradMethods::EvalData GradMethods::conjGrad(const GradMethods::QuadFunction &f,
                                            const Vector &x0,
                                            double eps,
                                            const UndimMethods::UndimMethod &undim_method) {
    EvalData data;
    Vector x = x0;
    Vector grad = gradF(f, x);
    Vector p = -grad;
    data.push_back(x);
    while (norm(grad) >= eps) {
        const double norm_grad_x = norm(grad);
        const double alpha = SQR(norm_grad_x) / (((*f.A) * p) * p);
        const Vector y = x + alpha * p;
        const Vector gedit = grad + alpha * ((*f.A)
                * p);
        const double norm_grad_y = norm(gedit);
        const double beta = SQR(norm_grad_y) / SQR(norm_grad_x);
        p = -gedit + beta * p;
        x = y;
        grad = gradF(f, x);
        data.push_back(x);
    }
    return data;
}