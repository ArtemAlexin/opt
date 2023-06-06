#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include "methods/grad_methods.h"

/**
 * @author VanyaCpp
 */

using namespace std;

double random1() {
    return abs(((double) rand() / (double) RAND_MAX));
}


grad_methods::quad_function gen_form(int n, int k) {
    double max_val = random1() * 20;
    double min_val = max_val / k;
    grad_methods::quad_function f;
    f.A.resize(n, vector<double>(n));
    vector<double> diag(n);
    diag[0] = max_val;
    diag[1] = min_val;
    for (int i = 2; i < n; ++i) {
        diag[i] = random1() * (max_val - min_val) + min_val;
    }
    std::random_device rd;
    std::mt19937 gen{rd()};
    shuffle(diag.begin(), diag.end(), gen);
    for (int i = 0; i < n; ++i) {
        f.A[i][i] = diag[i];
    }
    f.B.resize(n);
    for (int i = 0; i < n; ++i) {
        f.B[i] = random1() * 10;
    }
    f.C = random1() * 10;
//    f.GCC_K = k;
    return f;
}

pair<double, double> average_n_k(const grad_methods::method &method, int n, int k, undim_methods::method_t &um) {
    srand(time(nullptr));
    double med = 0;
    for (int i = 0; i < 10; ++i) {
        grad_methods::quad_function f = gen_form(n, k);
        grad_methods::eval_data data = method(f, f.B, 1e-3, um);
        med += data.size() - 1;
    }
    return {k, med / 10};
}

vector<pair<double, double>> gen_stat(const grad_methods::method &method, int n, undim_methods::method_t &um) {
    vector<pair<double, double>> stat;
    for (int k = 1; k <= 100; ++k) {
        stat.push_back(average_n_k(method, n, k, um));
    }
    return stat;
}

void print(grad_methods::quad_function f) {
    cout << f.A.size() << endl;
    for (int j = 0; j < f.A.size(); ++j) {
        for (int t = 0; t < f.A[j].size(); ++t) {
            cout << f.A[j][t] << ' ';
        }
        cout << endl;
    }
    cout << f.B.size() << endl;
    for (int j = 0; j < f.B.size(); ++j) {
        cout << f.B[j] << ' ';
    }
    cout << endl;
    cout << f.C << endl << endl;
}

//int main() {
//    vector<int> dims = {2, 3, 5, 10, 25, 100, 1000};  //  for more dims need matrix_t = vector<double>
//    for (int n : dims) {
//        vector<pair<double, double>> stat = gen_stat(grad_methods::quick_grad_descent, n);
//        //  draw graphic
//    }
//    return 0;
//}