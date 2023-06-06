#pragma once

#include <functional>
#include <vector>

namespace unidimensional_function_optimization {
    /**
     * This structure contain info about calculation process and result of algorithm
     * @field value - minimum point = algorithm's result
     * @field iteration_num - algorithm's number of iterations
     * @field time_millis - algorithm's running time
     */
    struct iteration_data {
        iteration_data(double a, double b, std::vector<double> &&xs, std::vector<double> &&fs)
                : a(a), b(b), xs(xs), fs(fs) {}

        // segment of function's domain
        double a;
        double b;

        // new points
        std::vector<double> xs;

        // f in new points
        std::vector<double> fs;
    };

    struct eval_data {
        eval_data() : time(clock()) {}

        void add_iteration(double a, double b, std::vector<double> &&xs, std::vector<double> &&fs) {
            iterations.emplace_back(a, b, std::forward<std::vector<double>&&>(xs),
                                    std::forward<std::vector<double>&&>(fs));
        }

        eval_data& finish_eval(double a, double b, double x) {
            min = x;
            min_segment = std::make_pair(a, b);
            time = clock() - time;
            return *this;
        }

        size_t function_calls() {
            size_t result = 0;
            for (auto &it : iterations) {
                result += it.xs.size();
            }
            return result;
        }

        double min;
        std::pair<double, double> min_segment;
        std::vector<iteration_data> iterations;
        clock_t time;
    };

    struct segment {
        double a;
        double b;
    };

    using func_t = std::function<double(double)>;
    using method_t = std::function<eval_data(func_t&, segment, double)>;

    struct to_eval {
        eval_data eval(const method_t &m) {
            return m(f, seg, eps);
        }

        func_t f;
        segment seg;
        double eps;
    };

    /**
     * 5 algorithms for unimodal function minimization
     * @param f - function for minimizing
     * @param [a, b] - segment for minimization
     * @param eps - limit of result's error
     * @returns - found minimum and metadata of calculation process (optional)
     */

    /// @see [about dichotomy method](https://en.wikipedia.org/wiki/Bisection_method)
    eval_data dichotomy_method(func_t &f, segment seg, double eps);

    /// @see [about golden section method](https://www.cs.ccu.edu.tw/~wtchu/courses/2014s_OPT/Lectures/Chapter%207%20One-Dimensional%20Search%20Methods.pdf)
    eval_data golden_section_method(func_t &f, segment seg, double eps);

    /// @see [about fibonacci method](https://www.cs.ccu.edu.tw/~wtchu/courses/2014s_OPT/Lectures/Chapter%207%20One-Dimensional%20Search%20Methods.pdf)
    eval_data fiboncci_method(func_t &f, segment seg, double eps);

    /// @see [about parabola method](http://fourier.eng.hmc.edu/e176/lectures/NM/node25.html)
    eval_data parabola_method(func_t &f, segment seg, double eps);

    /// @see [about brents method](https://www.wikiwand.com/en/Brent%27s_method)
    eval_data brents_method(func_t &f, segment seg, double eps);
}

