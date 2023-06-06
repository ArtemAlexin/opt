#pragma once

#include <functional>
#include <vector>
#include <time.h>

namespace UnidimMethods {
    /**
     * This structure contain info about calculation process and result of algorithm
     * @field value - minimum point = algorithm's result
     * @field iteration_num - algorithm's number of iterations
     * @field time_millis - algorithm's running time
     */
    struct IterationData {
        IterationData(double a, double b, std::vector<double> &&xs, std::vector<double> &&fs)
                : a(a), b(b), xs(xs), fs(fs) {}

        // segment of function's domain
        double a;
        double b;

        // new points
        std::vector<double> xs;

        // f in new points
        std::vector<double> fs;
    };

    struct EvalData {
        EvalData() : time(clock()) {}

        void addIteration(double a, double b, std::vector<double> &&xs, std::vector<double> &&fs) {
            iterations.emplace_back(a, b, std::forward<std::vector<double>&&>(xs),
                                    std::forward<std::vector<double>&&>(fs));
        }

        EvalData& finishEval(double a, double b, double x) {
            min = x;
            minSegment = std::make_pair(a, b);
            time = clock() - time;
            return *this;
        }

        size_t functionCalls() {
            size_t result = 0;
            for (auto &it : iterations) {
                result += it.xs.size();
            }
            return result;
        }

        double min;
        std::pair<double, double> minSegment;
        std::vector<IterationData> iterations;
        clock_t time;
    };

    struct Segment {
        double a;
        double b;
    };

    using UndimFunction = std::function<double(double)>;
    using UndimMethod = std::function<EvalData(UndimFunction&, Segment, double)>;


    /**
     * 5 algorithms for unimodal function minimization
     * @param f - function for minimizing
     * @param [a, b] - segment for minimization
     * @param eps - limit of result's error
     * @returns - found minimum and metadata of calculation process (optional)
     */

    /// @see [about dichotomy method](https://en.wikipedia.org/wiki/Bisection_method)
    EvalData dichotomyMethod(UndimFunction &f, Segment seg, double eps);

    /// @see [about golden section method](https://www.cs.ccu.edu.tw/~wtchu/courses/2014s_OPT/Lectures/Chapter%207%20One-Dimensional%20Search%20Methods.pdf)
    EvalData goldenSectionMethod(UndimFunction &f, Segment seg, double eps);

    /// @see [about fibonacci method](https://www.cs.ccu.edu.tw/~wtchu/courses/2014s_OPT/Lectures/Chapter%207%20One-Dimensional%20Search%20Methods.pdf)
    EvalData fiboncciMethod(UndimFunction &f, Segment seg, double eps);

    /// @see [about parabola method](http://fourier.eng.hmc.edu/e176/lectures/NM/node25.html)
    EvalData parabolaMethod(UndimFunction &f, Segment seg, double eps);

    /// @see [about brents method](https://www.wikiwand.com/en/Brent%27s_method)
    EvalData brentsMethod(UndimFunction &f, Segment seg, double eps);
}

