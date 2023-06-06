#include <gtest.h>

#include <QuadFunction.h>
#include <new_generators.h>
#include <quasi_newton_methods.h>
#include <unidim_methods.h>

TEST(BfsMethod, RandomDiagPosQuadFunctions) {
    for (size_t i = 0; i < 10; ++i) {
//        std::cerr << "test " << i << "\n";
        size_t dim = (1 + rand() % 100);
        Vector x0 = randomVector(dim, 10'000);
        CanonicalMatrix A = randomDiagPosData(dim);
        QuadFunction f(A, Vector(dim, 0), 0);
        auto x = QuasiNewtonMethods::bfs(
                x0,
                1e-7,
                f.function,
                f.gradient,
                f.gessian
        );
        EXPECT_LE(norm(x), dim);
    }
}

TEST(PowellMethod, RandomDiagPosQuadFunctions) {
    for (size_t i = 0; i < 10; ++i) {
//        std::cerr << "test " << i << "\n";
        size_t dim = (1 + rand() % 50);
        Vector x0 = randomVector(dim, 10'000);
        CanonicalMatrix A = randomDiagPosData(dim);
        QuadFunction f(A, Vector(dim, 0), 0);
        auto x = QuasiNewtonMethods::powell(
                x0,
                1e-7,
                f.function,
                f.gradient,
                f.gessian
        );
        EXPECT_LE(norm(x), dim);
    }
}

TEST(BfsNewton, Simple) {
    QuasiNewtonMethods::Function f = [](const Vector &x) {
        double res = 0;
        for (double t : x) {
            res += t * t;
        }
        return res;
    };
    QuasiNewtonMethods::Gradient gr = [](const Vector &x) {
        Vector y(x.size());
        for (int i = 0; i < y.size(); ++i) {
            for (int j = 0; j < x.size(); ++j) {
                if (i == j) {
                    y[i] += 2 * x[j];
                }
            }
        }
        return y;
    };
    QuasiNewtonMethods::Gessian hass = [](const Vector &x) {
        std::vector<std::vector<double>> v(x.size(), std::vector<double>(x.size()));
        for (int i = 0; i < x.size(); ++i) {
            for (int j = 0; j < x.size(); ++j) {
                for (int t = 0; t < x.size(); ++t) {
                    if (i == t && j == t) {
                        v[i][j] += 2;
                    }
                }
            }
        }
        return CanonicalMatrix(v);
    };

    std::vector<Vector> xs = {
            {0,    0,   0},
            {1,    1,   1},
            {1,    2,   -3},
            {0,    0,   2},
            {0,    0,   1e8},
            {0,    1e8, 1e8},
            {-1e8, 1e8, 1e8}
    };
    Vector expected = {0, 0, 0};
    for (Vector x0 : xs) {
        Vector ans = QuasiNewtonMethods::bfs(x0, 1e-6, f, gr, hass);
        for (int i = 0; i < expected.size(); ++i) {
            EXPECT_TRUE(abs(expected[i] - ans[i]) < 1e-6);
        }
    }
}

TEST(PowellNewton, Simple) {
    QuasiNewtonMethods::Function f = [](const Vector &x) {
        double res = 0;
        for (double t : x) {
            res += t * t;
        }
        return res;
    };
    QuasiNewtonMethods::Gradient gr = [](const Vector &x) {
        Vector y(x.size());
        for (int i = 0; i < y.size(); ++i) {
            for (int j = 0; j < x.size(); ++j) {
                if (i == j) {
                    y[i] += 2 * x[j];
                }
            }
        }
        return y;
    };
    QuasiNewtonMethods::Gessian hass = [](const Vector &x) {
        std::vector<std::vector<double>> v(x.size(), std::vector<double>(x.size()));
        for (int i = 0; i < x.size(); ++i) {
            for (int j = 0; j < x.size(); ++j) {
                for (int t = 0; t < x.size(); ++t) {
                    if (i == t && j == t) {
                        v[i][j] += 2;
                    }
                }
            }
        }
        return CanonicalMatrix(v);
    };

    std::vector<Vector> xs = {
            {0,    0,   0},
            {1,    1,   1},
            {1,    2,   -3},
            {0,    0,   2},
            {0,    0,   1e8},
            {0,    1e8, 1e8},
            {-1e8, 1e8, 1e8}
    };
    Vector expected = {0, 0, 0};
    for (Vector x0 : xs) {
        Vector ans = QuasiNewtonMethods::powell(x0, 1e-6, f, gr, hass);
        for (int i = 0; i < expected.size(); ++i) {
            EXPECT_TRUE(abs(expected[i] - ans[i]) < 1e-6);
        }
    }
}

TEST(BfsMethod, Hard) {
    QuasiNewtonMethods::Function f = [](const Vector &x) {
        return 1.1 * x[0] * x[0] + 1.8 * x[1] * x[1] + 2.1 * x[2] * x[2] +
               2.6 * x[0] * x[1] + 1.5 * x[0] * x[2] + 0.5 * x[1] * x[2];
    };
    QuasiNewtonMethods::Gradient gr = [](const Vector &x) {
        Vector v = {
                2.2 * x[0] + 2.6 * x[1] + 1.5 * x[2],
                2.6 * x[0] + 3.6 * x[1] + 0.5 * x[2],
                1.5 * x[0] + 0.5 * x[1] + 4.2 * x[2]
        };
        return v;
    };
    QuasiNewtonMethods::Gessian hass = [](const Vector &x) {
        return CanonicalMatrix({
                                       {2.2, 2.6, 1.5},
                                       {2.6, 3.6, 0.5},
                                       {1.5, 0.5, 4.2}
                               });
    };

    std::vector<Vector> xs = {
            {0,    0,   0},
            {1,    1,   1},
            {1,    2,   -3},
            {0,    0,   2},
            {0,    0,   1e8},
            {0,    1e8, 1e8},
            {-1e8, 1e8, 1e8}
    };
    Vector expected = {0, 0, 0};
    for (Vector x0 : xs) {
        Vector ans = QuasiNewtonMethods::bfs(x0, 1e-6, f, gr, hass);
        for (int i = 0; i < expected.size(); ++i) {
            EXPECT_TRUE(abs(expected[i] - ans[i]) < 1e-6);
        }
    }
}

TEST(PowellMethod, Hard) {
    QuasiNewtonMethods::Function f = [](const Vector &x) {
        return 1.1 * x[0] * x[0] + 1.8 * x[1] * x[1] + 2.1 * x[2] * x[2] +
               2.6 * x[0] * x[1] + 1.5 * x[0] * x[2] + 0.5 * x[1] * x[2];
    };
    QuasiNewtonMethods::Gradient gr = [](const Vector &x) {
        Vector v = {
                2.2 * x[0] + 2.6 * x[1] + 1.5 * x[2],
                2.6 * x[0] + 3.6 * x[1] + 0.5 * x[2],
                1.5 * x[0] + 0.5 * x[1] + 4.2 * x[2]
        };
        return v;
    };
    QuasiNewtonMethods::Gessian hass = [](const Vector &x) {
        return CanonicalMatrix({
                                       {2.2, 2.6, 1.5},
                                       {2.6, 3.6, 0.5},
                                       {1.5, 0.5, 4.2}
                               });
    };

    std::vector<Vector> xs = {
            {0,    0,   0},
            {1,    1,   1},
            {1,    2,   -3},
            {0,    0,   2},
            {0,    0,   1e8},
            {0,    1e8, 1e8},
            {-1e8, 1e8, 1e8}
    };
    Vector expected = {0, 0, 0};
    for (Vector x0 : xs) {
        Vector ans = QuasiNewtonMethods::powell(x0, 1e-7, f, gr, hass);
        for (int i = 0; i < expected.size(); ++i) {
            EXPECT_TRUE(abs(expected[i] - ans[i]) < 1e-3);
        }
    }
}

TEST(BfsMethod, Advanced) {
    QuasiNewtonMethods::Function f = [](const Vector &x) {
        return 1 + log(1.0/M_PI + x[0] * x[0] + x[1] * x[1]);
    };
    QuasiNewtonMethods::Gradient gr = [](const Vector &x) {
        Vector v = {
                (2 * x[1] * x[1] * x[0])/(1.0/M_PI  + x[0] * x[0] + x[1] * x[1]),
                (2 * x[1] * x[0] * x[0])/(1.0/M_PI  + x[0] * x[0] + x[1] * x[1])
        };
        return v;
    };
    QuasiNewtonMethods::Gessian hass = [](const Vector &x) {
        double denom = (x[0] * x[0] * x[1] * x[1] + 1.0/M_PI);
        return CanonicalMatrix({
                                       {-4 * (pow(x[1], 4) * x[0] * x[0])/pow(denom, 2)
                                        + 2 * (x[1] * x[1])/denom,
                                               -4 * (pow(x[1], 3) * pow(x[0], 3))/pow(denom, 2)
                                               + 4 * (x[0] * x[1])/denom},
                                       {-4 * (pow(x[1], 3) * pow(x[0], 3))/pow(denom, 2)
                                        + 4 * (x[0] * x[1])/denom,
                                               -4 * (pow(x[0], 4) * x[1] * x[1])/pow(denom, 2)
                                               + 2 * (x[0] * x[0])/denom}
                               });
    };

    std::vector<Vector> xs = {
            {0,    0},
            {1,    1},
            {1,    2},
            {-3,   -7},
            {0,    100},
            {100,    100}
    };
    Vector expected = {0, 0, 0};
    for (Vector x0 : xs) {
        Vector ans = QuasiNewtonMethods::bfs(x0, 1e-7, f, gr, hass);
        EXPECT_TRUE(abs(ans[0]) < 1e-3 || abs(ans[1]) < 1e-3);
    }
}

TEST(PowellMethod, Advanced) {
    QuasiNewtonMethods::Function f = [](const Vector &x) {
        return 1 + log(1.0/M_PI + x[0] * x[0] + x[1] * x[1]);
    };
    QuasiNewtonMethods::Gradient gr = [](const Vector &x) {
        Vector v = {
                (2 * x[1] * x[1] * x[0])/(1.0/M_PI  + x[0] * x[0] + x[1] * x[1]),
                (2 * x[1] * x[0] * x[0])/(1.0/M_PI  + x[0] * x[0] + x[1] * x[1])
        };
        return v;
    };
    QuasiNewtonMethods::Gessian hass = [](const Vector &x) {
        double denom = (x[0] * x[0] * x[1] * x[1] + 1.0/M_PI);
        return CanonicalMatrix({
                                       {-4 * (pow(x[1], 4) * x[0] * x[0])/pow(denom, 2)
                                        + 2 * (x[1] * x[1])/denom,
                                               -4 * (pow(x[1], 3) * pow(x[0], 3))/pow(denom, 2)
                                               + 4 * (x[0] * x[1])/denom},
                                       {-4 * (pow(x[1], 3) * pow(x[0], 3))/pow(denom, 2)
                                        + 4 * (x[0] * x[1])/denom,
                                               -4 * (pow(x[0], 4) * x[1] * x[1])/pow(denom, 2)
                                               + 2 * (x[0] * x[0])/denom}
                               });
    };

    std::vector<Vector> xs = {
            {0,    0},
            {1,    1},
            {1,    2},
            {-3,   -7},
            {0,    100},
            {100,    100}
    };
    Vector expected = {0, 0, 0};
    for (Vector x0 : xs) {
        Vector ans = QuasiNewtonMethods::powell(x0, 1e-7, f, gr, hass);
        EXPECT_TRUE(abs(ans[0]) < 1e-5 || abs(ans[1]) < 1e-5);
    }
}

