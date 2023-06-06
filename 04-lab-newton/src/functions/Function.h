#pragma once

#include <CanonicalMatrix.h>
#include <Vector.h>

struct Function {
    using Function = std::function<double(const Vector &)>;
    using Gradient = std::function<Vector(const Vector &)>;
    using Gessian = std::function<CanonicalMatrix(const Vector &)>;

    Function(const Function& function, const Gradient& gradient, const Gessian& gessian)
    : function(function),
      gradient(gradient),
      gessian(gessian) {}

    Function function;
    Gradient gradient;
    Gessian gessian;
};