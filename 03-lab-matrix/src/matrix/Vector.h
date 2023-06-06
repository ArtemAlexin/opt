#pragma once

#include <istream>
#include <fstream>
#include <vector>

using Vector = std::vector<double>;

inline std::istream &operator>>(std::istream &in, Vector &v) {
    for (int i = 0; i < v.size(); ++i) {
        in >> std::fixed >> v[i];
    }
    return in;
}

inline std::ostream &operator<<(std::ostream &out, Vector &v) {
    for (double &value : v) {
        out << std::fixed << value << ' ';
    }
    return out;
}

inline Vector readFromFile(size_t dim, const std::string &file) {
    std::ifstream fin(file);
    Vector v(dim);
    fin >> v;
    return v;
}