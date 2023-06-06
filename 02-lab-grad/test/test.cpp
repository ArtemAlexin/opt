#include "methods/grad_methods.h"
#include <bits/stdc++.h>
#include "undim_methods/undim_methods.h"

using namespace std;
using namespace grad_methods;

struct testable {
    method m;
    quad_function f;
    double valid_fx;
};

quad_function f1 = {
        {{128, 126},
         {126, 128}},
        {-10, 30},
        13
};

quad_function f2 = {
        {{608, 506},
         {506, 608}},
        {50, 130},
        -111
};

quad_function f3 = {
        {{2}},
        {2},
        1
};

quad_function asshole = {
        {{1, 0}, {0, 1}},
        {-1, -1},
        1
};

//void test(const testable& t, double eps) {
//    eval_data_t method_answer = t.method(t.f, eps, undim_methods::golden_section_method);
//    if (abs(method_answer.fx - t.valid_fx) < eps) {
//        printf("OK\n");
//    } else {
//        printf("FAILED:\noutput: f(x)=%f\ncorrect: f(x)=%f\n", method_answer.fx, t.valid_fx);
//    }
//}

int main() {
//    test({grad_methods::conjugate_grad, f1, -187.393699}, 1e-3);
//    test({grad_methods::conjugate_grad, f2, -133.957370}, 1e-3);
//    test({grad_methods::conjugate_grad, f3, 0}, 1e-3);
//    test({grad_methods::conjugate_grad, asshole, 0}, 1e-3);
}
