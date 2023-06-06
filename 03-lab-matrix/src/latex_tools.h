#pragma once

#include <iomanip>

using latex_table_data_t = std::vector<std::vector<double>>;
using latex_line_data_t = std::vector<double>;

inline std::string repeat(const std::string &str, size_t num) {
    std::string result;
    result.reserve(str.size() * num);
    while (num--) {
        result += str;
    }
    return result;
}

inline std::string toLatexLine(const latex_line_data_t &data) {
    std::stringstream out;
    out << "\\hline ";
    for (size_t j = 0; j + 1 < data.size(); ++j) {
        out << std::setprecision(10) << data[j] << " & ";
    }
    out << data.back() << " \\\\\n";
    return out.str();
}

/** Returns string representation of latex table with content from `data`*/
inline std::string toLatexTable(const latex_table_data_t &data) {
    std::stringstream out;
    size_t n = data.size();
    size_t m = data[0].size();
    assert(n != 0);
    out << "\\begin{center}\n" << "\\begin{tabular}" << "{|" << repeat(" c |", m) << "}" << "\n" << "\\hline\n";
    for (size_t i = 0; i < n; ++i) {
        out << toLatexLine(data[i]);
    }
    out << "\\hline\n" << "\\end{tabular}\n" << "\\end{center}\n";
    return out.str();
}

inline double absError(const Vector &x, const Vector &xTrue) {
    return norm(x - xTrue) / 3208;
}

inline double relativeError(const Vector &x, const Vector &xTrue) {
    return absError(x, xTrue) / norm(xTrue);
}

inline double cond(const Matrix &A, const Vector &b, const Vector &x, const Vector &xTrue) {
    return std::max(1., relativeError(x, xTrue) / (norm(b - A * x) / norm(b)));
}

inline latex_line_data_t dataLine(size_t n,
                                    const Matrix &A,
                                    const Vector &b,
                                    const Vector &xTrue,
                                    const Vector &x,
                                    const EvalData &evalData) {
    return {
            static_cast<double>(n),
            static_cast<double>(evalData.iterationsNumber),
            absError(x, xTrue),
            relativeError(x, xTrue),
            cond(A, b, x, xTrue)
    };
}