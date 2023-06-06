#pragma once

grad_methods::quad_function gen_form(int n, int k);

std::vector<std::pair<double, double>> gen_stat(const grad_methods::method &method, int n, undim_methods::method_t&);