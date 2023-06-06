#pragma once

#include <Vector.h>

namespace Logging {
    using EvalData = std::vector<Vector>;

    using Function = std::function<double(const Vector &)>;
    using Gradient = std::function<Vector(const Vector &)>;
    using Gessian = std::function<CanonicalMatrix(const Vector &)>;

    using Method = std::function<Vector(const Vector &, double, Function &, Gradient &, Gessian &, EvalData &)>;
}

