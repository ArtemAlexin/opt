#include "unidimensional_function_optimization.h"
#include <cmath>
#include <cassert>

namespace unidimensional_function_optimization {
    eval_data dichotomy_method(func_t &f, segment seg, double eps) {
        assert(eps > 0);
        assert(seg.a <= seg.b);

        eval_data data_;

        const double delta = eps / 4;

        while ((seg.b - seg.a) >= 2 * eps) {
            double x1 = (seg.a + seg.b - delta) / 2;
            double x2 = (seg.a + seg.b + delta) / 2;

            double f1 = f(x1);
            double f2 = f(x2);

            data_.add_iteration(seg.a, seg.b, {x1, x2}, {f1, f2});

            if (f1 <= f2) {
                //  [a_k+1, b_k+1] = [a_k, x2]
                seg.b = x2;
            } else {
                //  [a_k+1, b_k+1] = [x1, b_k]
                seg.a = x1;
            }
        }

        return data_.finish_eval(seg.a, seg.b, (seg.a + seg.b) / 2);
    }

    eval_data golden_section_method(func_t &f, segment seg, double eps) {
        assert(eps > 0);
        assert(seg.a <= seg.b);

        eval_data data_;

        const double phi = (sqrt(5) - 1) / 2;

        double x1 = seg.b - phi * (seg.b - seg.a);
        double x2 = seg.a + phi * (seg.b - seg.a);

        double f1 = f(x1);
        double f2 = f(x2);

        data_.add_iteration(seg.a, seg.b, {x1, x2}, {f1, f2});

        while (seg.b - seg.a > eps) {
            if (f1 <= f2) {
                // (a_{k+1}, b_{k+1}) = (a_k, x_2^k)
                // sample_f(x_2^{k+1}) = sample_f(x_1^k)
                seg.b = x2;
                x2 = x1;
                f2 = f1;
                x1 = seg.b - phi * (seg.b - seg.a);
                f1 = f(x1);
                data_.add_iteration(seg.a, seg.b, {x1}, {f1});
            } else {
                // (a_{k+1}, b_{k+1}) = (x_1^k, b_k)
                // sample_f(x_1^{k+1}) = sample_f(x_2^k)
                seg.a = x1;
                x1 = x2;
                f1 = f2;
                x2 = seg.a + phi * (seg.b - seg.a);
                f2 = f(x2);
                data_.add_iteration(seg.a, seg.b, {x2}, {f2});
            }
        }

        return data_.finish_eval(seg.a, seg.b, (seg.a + seg.b) / 2);
    }

    using fib_pair_t = std::pair<uint64_t, uint64_t>;

    // (F_n, F_{n+1}) where F_n is n-th Fibonacci number
    fib_pair_t fib_n_fib_n_plus_1(size_t n) {
        uint64_t fst = 0;
        uint64_t snd = 1;
        for (; n > 0; --n) {
            uint64_t tmp = fst;
            fst = snd;
            snd += tmp;
        }
        return std::make_pair(fst, snd);
    }

    // (F_n, F_{n+1}) -> (F_{n-1}, F_n)
    void set_previous_fib_pair(fib_pair_t &p) {
        uint64_t tmp = p.second;
        p.second = p.first;
        p.first = tmp - p.second;
    }

    eval_data fiboncci_method(func_t &f, segment seg, double eps) {
        assert(eps > 0);
        assert(seg.a <= seg.b);

        eval_data data_;

        const double phi_inv = (sqrt(5) + 1) / 2;

        // number of iterations
        size_t n = log(sqrt(5) * (seg.b - seg.a) / eps) / log(phi_inv) - 2;

        // (F_n, F_{n+1})
        fib_pair_t fibs = fib_n_fib_n_plus_1(n);

        // F_{n+2}
        const uint64_t fib_n_plus_2 = fibs.first + fibs.second;

        const double delta = seg.b - seg.a;

        // x_1^0, x_2^0
        double x1 = seg.a + static_cast<double>(fibs.first) / fib_n_plus_2 * delta;
        double x2 = seg.a + static_cast<double>(fibs.second) / fib_n_plus_2 * delta;

        // sample_f(x_1), sample_f(x_2)
        double f1 = f(x1);
        double f2 = f(x2);

        data_.add_iteration(seg.a, seg.b, {x1, x2}, {f1, f2});

        // let k is number of passed iterations
        for (; n > 0; --n) {
            // (F_{n-k+1}, F_{n-k+2}) -> (F_{n-k}, F_{n-k+1})
            set_previous_fib_pair(fibs);

            if (f1 <= f2) {
                // (a_{k+1}, b_{k+1}) = (a_k, x2)
                seg.b = x2;

                // x_1^{k+1}, x_2^{k+1}
                x2 = x1;
                x1 = seg.a + static_cast<double>(fibs.first) / fib_n_plus_2 * delta;

                // sample_f(x_1^{k+1}), sample_f(x_2^{k+1})
                f2 = f1;
                f1 = f(x1);

                data_.add_iteration(seg.a, seg.b, {x1}, {f1});
            } else {
                // (a_{k+1}, b_{k+1}) = (x1, b_k)
                seg.a = x1;

                // x_1^{k+1}, x_2^{k+1}
                x1 = x2;
                x2 = seg.a + static_cast<double>(fibs.second) / fib_n_plus_2 * delta;

                // sample_f(x_1^{k+1}), sample_f(x_2^{k+1})
                f1 = f2;
                f2 = f(x2);

                data_.add_iteration(seg.a, seg.b, {x2}, {f2});
            }
        }

        return data_.finish_eval(seg.a, seg.b, (seg.a + seg.b) / 2);
    }

    /**
     *
     * works only for strict unimodal functions
     */
    eval_data parabola_method(func_t &f, segment seg, double eps) {
        assert(eps > 0);
        assert(seg.a <= seg.b);

        eval_data data_;

        double x1 = seg.a;
        double x2 = (seg.a + seg.b) / 2;
        double x3 = seg.b;

        double x_last = 0;
        double x_curr = 0;

        double f1 = f(x1);
        double f2 = f(x2);
        double f3 = f(x3);

//        data_.add_iteration(seg.a, seg.b, {x1, x2, x3}, {f1, f2, f3});

        while (x_last == 0 || std::abs(x_curr - x_last) >= eps / 12) {
            data_.add_iteration(0, 0, {x1, x2, x3}, {f1, f2, f3});

            if (x1 == x2 || x2 == x3) {
                break;
            }

            double a1 = (f2 - f1) / (x2 - x1);
            double a2 = ((f3 - f1) / (x3 - x1) - (f2 - f1) / (x2 - x1)) / (x3 - x2);

            x_last = x_curr;
            x_curr = (x1 + x2 - a1 / a2) / 2;
            double f_x_curr = f(x_curr);

            data_.add_iteration(seg.a, seg.b, {x_curr}, {f_x_curr});

            if (x1 < x_curr && x_curr < x2) {
                if (f_x_curr >= f2) {
                    x1 = x_curr;
                    f1 = f_x_curr;
                } else {
                    x3 = x2;
                    f3 = f2;
                    x2 = x_curr;
                    f2 = f_x_curr;
                }
            } else {
                if (f_x_curr <= f2) {
                    x1 = x2;
                    f1 = f2;
                    x2 = x_curr;
                    f2 = f_x_curr;
                } else {
                    x3 = x_curr;
                    f3 = f_x_curr;
                }
            }
        }

        return data_.finish_eval(seg.a, seg.b, x_curr);
    }

    static const double golden = 0.3819660f;

    eval_data brents_method(func_t &f, segment seg, double eps) {
        assert(eps > 0);
        assert(seg.a <= seg.b);

        eval_data data_;

        double x;  // x_min
        double w;  // second best point
        double v;  // previous value of w
        double u;  // most recent evaluation point
        double delta; // The distance moved in the last step
        double delta2; // The distance moved in the step before last
        double fu, fv, fw, fx; // function evaluations at u, v, w, x
        double mid; // midpoint of min and max
        double fract1; // minimal relative movement in x

        x = w = v = seg.b;
        fw = fv = fx = f(x);
        delta2 = delta = 0;

        data_.add_iteration(seg.a, seg.b, {x, w, v}, {fx, fw, fv});

        while (true) {
            mid = (seg.a + seg.b) / 2;
            fract1 = eps * fabs(x) + eps / 10;
            // everything is done, work out
            if (fabs(x - mid) + (seg.b - seg.a) / 2 <= 2 * fract1) {
                break;
            }
            // parabola_method_part
            if (fabs(delta2) > fract1) {
                double r = (x - w) * (fx - fv);
                double q = (x - v) * (fx - fw);
                double p = (x - v) * q - (x - w) * r;
                q = 2 * (q - r);
                if (q > 0)
                    p = -p;
                q = fabs(q);
                double td = delta2;
                delta2 = delta;
                // find out if this step acceptable or not
                if ((fabs(p) >= fabs(q * td / 2)) || (p <= q * (seg.a - x)) || (p >= q * (seg.b - x))) {
                    // try golden section method part
                    delta2 = (x >= mid) ? seg.a - x : seg.b - x;
                    delta = golden * delta2;
                } else {
                    // parabola method part fits
                    delta = p / q;
                    u = x + delta;
                    if (((u - seg.a) < 2 * fract1) || ((seg.b - u) < 2 * fract1)) {
                        delta = (mid - x) < 0 ? -fabs(fract1) : fabs(fract1);
                    }
                }
            } else {
                // golden section part
                delta2 = (x >= mid) ? seg.a - x : seg.b - x;
                delta = golden * delta2;
            }
            // update current point
            u = (fabs(delta) >= fract1) ? x + delta : (delta > 0 ? x + fabs(fract1) :
                                                       x - fabs(fract1));
            fu = f(u);
            data_.add_iteration(seg.a, seg.b, {u}, {fu});
            if (fu <= fx) {
                // got improvement
                if (u >= x) {
                    seg.a = x;
                } else {
                    seg.b = x;
                }
                // update all vars
                v = w;
                w = x;
                x = u;
                fv = fw;
                fw = fx;
                fx = fu;
            } else {
                // u is worse than we already have, but it should be better than one of other out pints
                if (u < x) {
                    seg.a = u;
                } else {
                    seg.b = u;
                }
                if ((fu <= fw) || (w == x)) {
                    // us is better than w
                    v = w;
                    w = u;
                    fv = fw;
                    fw = fu;
                } else if ((fu <= fv) || (v == x) || (v == w)) {
                    // u is better than u
                    v = u;
                    fv = fu;
                }
            }
        }
        return data_.finish_eval(seg.a, seg.b, x);
    }
}
