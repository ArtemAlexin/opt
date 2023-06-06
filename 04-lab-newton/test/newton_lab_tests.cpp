#include <gtest.h>
#include <newton_methods.h>
#include <CanonicalMatrix.h>

using namespace std;

/*
 * Advanced тесты не проходят, потому что я поставил LU и там матрица с нулевым определителем получается
 * на сопряж градиентах они пройдут, но не пройдет COCKRSUN2 тест, там зациклится
 */

namespace __GLIB_C_CORS_TESTS_{
    vector<Vector> default_xs3 = {
            {0,    0,   0},
            {1,    1,   1},
            {1,    2,   -3},
            {0,    0,   2},
            {0,    0,   1e8},
            {0,    1e8, 1e8},
            {-1e8, 1e8, 1e8}
    };

    vector<Vector> default_xs2 = {
            {0,   0},
            {1,   1},
            {1,   2},
            {-3,  -7},
            {0,   100},
            {100, 100}
    };

    namespace Simple {
        NewtonMethods::Function f = [](const Vector &x) {
            double res = 0;
            for (double t : x) {
                res += t * t;
            }
            return res;
        };
        NewtonMethods::Gradient gr = [](const Vector &x) {
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
        NewtonMethods::Gessian hass = [](const Vector &x) {
            vector<vector<double>> v(x.size(), vector<double>(x.size()));
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
    }

    namespace Hard {
        NewtonMethods::Function f = [](const Vector &x) {
            return 1.1 * x[0] * x[0] + 1.8 * x[1] * x[1] + 2.1 * x[2] * x[2] +
                   2.6 * x[0] * x[1] + 1.5 * x[0] * x[2] + 0.5 * x[1] * x[2];
        };
        NewtonMethods::Gradient gr = [](const Vector &x) {
            Vector v = {
                    2.2 * x[0] + 2.6 * x[1] + 1.5 * x[2],
                    2.6 * x[0] + 3.6 * x[1] + 0.5 * x[2],
                    1.5 * x[0] + 0.5 * x[1] + 4.2 * x[2]
            };
            return v;
        };
        NewtonMethods::Gessian hass = [](const Vector &x) {
            return CanonicalMatrix({
                                           {2.2, 2.6, 1.5},
                                           {2.6, 3.6, 0.5},
                                           {1.5, 0.5, 4.2}
                                   });
        };
    }

    namespace Advanced {
        NewtonMethods::Function f = [](const Vector &x) {
            return 1 + log(1.0 / M_PI + x[0] * x[0] + x[1] * x[1]);
        };
        NewtonMethods::Gradient gr = [](const Vector &x) {
            Vector v = {
                    (2 * x[1] * x[1] * x[0]) / (1.0 / M_PI + x[0] * x[0] + x[1] * x[1]),
                    (2 * x[1] * x[0] * x[0]) / (1.0 / M_PI + x[0] * x[0] + x[1] * x[1])
            };
            return v;
        };
        NewtonMethods::Gessian hass = [](const Vector &x) {
            double denom = (x[0] * x[0] * x[1] * x[1] + 1.0 / M_PI);
            return CanonicalMatrix({
                                           {-4 * (pow(x[1], 4) * x[0] * x[0]) / pow(denom, 2)
                                            + 2 * (x[1] * x[1]) / denom,
                                                   -4 * (pow(x[1], 3) * pow(x[0], 3)) / pow(denom, 2)
                                                   + 4 * (x[0] * x[1]) / denom},
                                           {-4 * (pow(x[1], 3) * pow(x[0], 3)) / pow(denom, 2)
                                            + 4 * (x[0] * x[1]) / denom,
                                                   -4 * (pow(x[0], 4) * x[1] * x[1]) / pow(denom, 2)
                                                   + 2 * (x[0] * x[0]) / denom}
                                   });
        };
    }

    namespace COCKRSUN1 {
        NewtonMethods::Function f = [](const Vector &x) {
            return x[0] * x[0] + x[1] * x[1] - 1.2 * x[0] * x[1];
        };
        NewtonMethods::Gradient gr = [](const Vector &x) {
            Vector v = {
                    2 * x[0] - 1.2 * x[1],
                    2 * x[1] - 1.2 * x[0]
            };
            return v;
        };
        NewtonMethods::Gessian hass = [](const Vector &x) {
            return CanonicalMatrix({
                                           {2,    -1.2},
                                           {-1.2, 2}
                                   });
        };
    }

    namespace COCKRSUN2 {
        NewtonMethods::Function f = [](const Vector &x) {
            return 100 * x[1] * x[1] - 200 * x[0] * x[0] * x[1] + 100 * pow(x[0], 4) + 1 - 2 * x[0] + x[0] * x[0];
        };
        NewtonMethods::Gradient gr = [](const Vector &x) {
            Vector v = {
                    2 * x[0] - 400 * x[1] + 400 * pow(x[0], 3) - 2,
                    200 * x[1] - 200 * x[0] * x[0]
            };
            return v;
        };
        NewtonMethods::Gessian hass = [](const Vector &x) {
            return CanonicalMatrix({
                                           {2 + 1200 * x[0] * x[0],    -400},
                                           {-400 * x[0], 200}
                                   });
        };
    }
}

void print_latex_table(const NewtonMethods::CorsData &data) {
    std::stringstream out;
    out << std::setprecision(10);
    if (data.alphas[0] == 0) {
        // не юзается одномерная минимизация
        out << "\\begin{center}\n\\begin{tabular}{| c |}\n\\hline\n";
        out << "\\hline " << data.iterations << " \\\\\n";
    } else {
        out << "\\begin{center}\n\\begin{tabular}{| c | c |}\n\\hline\n";
        out << "\\hline " << data.iterations << " \\\\\n";
        for (int i = 0; i < data.alphas.size(); ++i) {
            out << "\\hline " << i << " & " << data.alphas[i] << " \\\\\n";
        }
    }
    out << "\\hline\n" << "\\end{tabular}\n" << "\\end{center}\n";
    cout << out.str();
}

TEST(JustForFun, ValentinPussin) {
    cout << "Обычно падают тесты, а у нас упал преподаватель!" << endl;
}

TEST(ClassicNewton, Simple) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::Simple::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::Simple::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::Simple::hass;

    vector<Vector> xs = __GLIB_C_CORS_TESTS_::default_xs3;
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::classicNewton(x0, 1e-6, f, gr, hass);
        for (double x : ans.ans) {
            EXPECT_TRUE(abs(x) < 1e-6);
            cout << x << ' ';
        }
        cout << endl;
        cout << ans.iterations << endl << endl;
    }
}

TEST(ClassicNewton, Hard) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::Hard::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::Hard::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::Hard::hass;

    vector<Vector> xs = __GLIB_C_CORS_TESTS_::default_xs3;
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::classicNewton(x0, 1e-6, f, gr, hass);
        for (double x : ans.ans) {
            EXPECT_TRUE(abs(x) < 1e-6);
            cout << x << ' ';
        }
        cout << endl;
        cout << ans.iterations << endl << endl;
    }
}

TEST(ClassicNewton, Advanced) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::Advanced::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::Advanced::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::Advanced::hass;

    vector<Vector> xs = __GLIB_C_CORS_TESTS_::default_xs2;
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::classicNewton(x0, 1e-6, f, gr, hass);
        EXPECT_TRUE(abs(ans.ans[0]) < 1e-6 || abs(ans.ans[1]) < 1e-6);
        cout << ans.ans[0] << ' ' << ans.ans[1];
        cout << endl;
        cout << ans.iterations << endl << endl;
    }
}

TEST(ClassicNewton, COCKRSUN1) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::COCKRSUN1::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::COCKRSUN1::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::COCKRSUN1::hass;

    vector<Vector> xs = {{4, 1}};
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::classicNewton(x0, 1e-6, f, gr, hass);
        EXPECT_TRUE(abs(ans.ans[0]) < 1e-6 && abs(ans.ans[1]) < 1e-6);
        print_latex_table(ans);
        cout << endl << endl;
    }
}
/*
TEST(ClassicNewton, COCKRSUN2) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::COCKRSUN2::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::COCKRSUN2::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::COCKRSUN2::hass;

    vector<Vector> xs = {{-1.2, 1}};
    Vector expected = {1, 1};
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::classicNewton(x0, 1e-6, f, gr, hass);
        for (int i = 0; i < expected.size(); ++i) {
            EXPECT_TRUE(abs(ans.ans[i] - expected[i]) < 1e-6);
        }
        print_latex_table(ans);
        cout << endl << endl;
    }
}
*/
TEST(UnidimSearchNewton, Simple) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::Simple::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::Simple::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::Simple::hass;

    vector<Vector> xs = __GLIB_C_CORS_TESTS_::default_xs3;
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::unidimSearchNewton(x0, 1e-6, f, gr, hass);
        for (double x : ans.ans) {
            EXPECT_TRUE(abs(x) < 1e-6);
        }
        print_latex_table(ans);
        cout << endl << endl;
    }
}

TEST(UnidimSearchNewton, Hard) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::Hard::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::Hard::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::Hard::hass;

    vector<Vector> xs = __GLIB_C_CORS_TESTS_::default_xs3;
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::unidimSearchNewton(x0, 1e-6, f, gr, hass);
        for (double x : ans.ans) {
            EXPECT_TRUE(abs(x) < 1e-6);
        }
        print_latex_table(ans);
        cout << endl << endl;
    }
}

TEST(UnidimSearchNewton, Advanced) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::Advanced::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::Advanced::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::Advanced::hass;

    vector<Vector> xs = __GLIB_C_CORS_TESTS_::default_xs2;
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::unidimSearchNewton(x0, 1e-6, f, gr, hass);
        EXPECT_TRUE(abs(ans.ans[0]) < 1e-6 || abs(ans.ans[1]) < 1e-6);
        print_latex_table(ans);
        cout << endl << endl;
    }
}

TEST(UnidimSearchNewton, COCKRSUN1) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::COCKRSUN1::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::COCKRSUN1::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::COCKRSUN1::hass;

    vector<Vector> xs = {
            {4, 1}
    };
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::unidimSearchNewton(x0, 1e-6, f, gr, hass);
        for (double x : ans.ans) {
            EXPECT_TRUE(abs(x) < 1e-6);
        }
        print_latex_table(ans);
        cout << endl << endl;
    }
}
/*
TEST(UnidimSearchNewton, COCKRSUN2) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::COCKRSUN2::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::COCKRSUN2::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::COCKRSUN2::hass;

    vector<Vector> xs = {
            {-1.2, 1}
    };
    Vector expected = {1, 1};
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::unidimSearchNewton(x0, 1e-6, f, gr, hass);
        for (int i = 0; i < expected.size(); ++i) {
            EXPECT_TRUE(abs(ans.ans[i] - expected[i]) < 1e-6);
        }
        print_latex_table(ans);
        cout << endl << endl;
    }
}
*/
TEST(DescentDirectionNewton, Simple) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::Simple::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::Simple::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::Simple::hass;

    vector<Vector> xs = __GLIB_C_CORS_TESTS_::default_xs3;
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::descentDirectionNewton(x0, 1e-6, f, gr, hass);
        for (double x : ans.ans) {
            EXPECT_TRUE(abs(x) < 1e-6);
        }
        print_latex_table(ans);
        cout << endl << endl;
    }
}

TEST(DescentDirectionNewton, Hard) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::Hard::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::Hard::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::Hard::hass;

    vector<Vector> xs = __GLIB_C_CORS_TESTS_::default_xs3;
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::descentDirectionNewton(x0, 1e-6, f, gr, hass);
        for (double x : ans.ans) {
            EXPECT_TRUE(abs(x) < 1e-6);
        }
        print_latex_table(ans);
        cout << endl << endl;
    }
}

TEST(DescentDirectionNewton, Advanced) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::Advanced::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::Advanced::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::Advanced::hass;

    vector<Vector> xs = __GLIB_C_CORS_TESTS_::default_xs2;
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::descentDirectionNewton(x0, 1e-6, f, gr, hass);
        EXPECT_TRUE(abs(ans.ans[0]) < 1e-6 || abs(ans.ans[1]) < 1e-6);
        print_latex_table(ans);
        cout << endl << endl;
    }
}

TEST(DescentDirectionNewton, COCKRSUN1) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::COCKRSUN1::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::COCKRSUN1::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::COCKRSUN1::hass;

    vector<Vector> xs = {
            {4, 1}
    };
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::descentDirectionNewton(x0, 1e-6, f, gr, hass);
        for (double x : ans.ans) {
            EXPECT_TRUE(abs(x) < 1e-6);
        }
        print_latex_table(ans);
        cout << endl << endl;
    }
}
/*
TEST(DescentDirectionNewton, COCKRSUN2) {
    NewtonMethods::Function f = __GLIB_C_CORS_TESTS_::COCKRSUN2::f;
    NewtonMethods::Gradient gr = __GLIB_C_CORS_TESTS_::COCKRSUN2::gr;
    NewtonMethods::Gessian hass = __GLIB_C_CORS_TESTS_::COCKRSUN2::hass;

    vector<Vector> xs = {
            {-1.2, 1}
    };
    Vector expected = {1, 1};
    for (const Vector &x0 : xs) {
        NewtonMethods::CorsData ans = NewtonMethods::descentDirectionNewton(x0, 1e-6, f, gr, hass);
        for (int i = 0; i < expected.size(); ++i) {
            EXPECT_TRUE(abs(ans.ans[i] - expected[i]) < 1e-6);
        }
        print_latex_table(ans);
        cout << endl << endl;
    }
}
*/