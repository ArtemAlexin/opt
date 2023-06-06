#include <algorithm>
#include <gtest.h>

#include <ProfileMatrix.h>
#include <LUMatrix.h>
#include <LinearSystem.h>
#include <CanonicalMatrix.h>
#include <SparseMatrix.h>

#include <latex_tools.h>

#include <old_generators.h>
#include <new_generators.h>

using namespace std;

const int N_GEN = 10;

TEST(Matrix, Production) {
    for (size_t i = 0; i < 1000; ++i) {
        size_t n = rand() % 91 + 10;
        vector<vector<double>> data = rand() % 2 == 0 ? randomData(n) : randomRawSeqData(n);
        ProfileMatrix p = data;
        SparseMatrix s = data;
        CanonicalMatrix c = data;
        Vector v = randomVector(n);
        Vector vp = p * v;
        Vector vs = s * v;
        Vector vc = c * v;
        for (size_t j = 0; j < n; ++j) {
            EXPECT_LE(std::abs(vc[j] - vp[j]), 1e-7);
            EXPECT_LE(std::abs(vc[j] - vs[j]), 1e-7);
        }
    }
}

//TEST(Matrix, CorrectContentOfZeroMatrix) {
//    Matrix m(100);
//    for (size_t i = 0; i < 10; ++i) {
//        for (size_t j = 0; j < 10; ++j) {
//            EXPECT_DOUBLE_EQ(0., m.get(i, j));
//        }
//    }
//}
//
//TEST(Matrix, CorrectContentOfNonZeroMatrix) {
//    vector<vector<double>> data =
//            {
//            {0, 0, 0, 0, 0, 0, 1, 2, 3, 4},
//            {0, 0, 1, 0, 0, 0, 1, 2, 3, 4},
//            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//            {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
//            {0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
//            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
//            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
//            {0, 0, 3, 0, 0, 0, 0, 0, 0, 0},
//            };
//    Matrix m = data;
//    for (size_t i = 0; i < 10; ++i) {
//        for (size_t j = 0; j < 10; ++j) {
//            EXPECT_DOUBLE_EQ(data[i][j], m.get(i, j));
//        }
//    }
//}

//TEST(Matrix, CorrectContentRandom) {
//    vector<vector<double>> data(100, vector<double>(100));
//    auto gen = [](){
//        return ((rand() % 100 < 60) ? 0 : (1 + rand() % 100));
//    };
//    for (auto &row : data) {
//        std::generate(row.begin(), row.end(), gen);
//    }
//    Matrix m = data;
//    for (size_t i = 0; i < 10; ++i) {
//        for (size_t j = 0; j < 10; ++j) {
//            EXPECT_DOUBLE_EQ(data[i][j], m.get(i, j));
//        }
//    }
//}

//TEST(Matrix, IO) {
//    ifstream fin("../tests/matrix_io/matrix.in");
//    Matrix m(7);
//    fin >> m;
//
//    fin.clear();
//    fin.seekg(0);
//    vector<vector<double>> data(7);
//    for (size_t i = 0; i < 7; ++i) {
//        for (size_t  j = 0; j < 7; ++j) {
//            double value;
//            fin >> value;
//            data[i].push_back(value);
//        }
//    }
//
//    for (size_t i = 0; i < 7; ++i) {
//        for (size_t j = 0; j < 7; ++j) {
//            EXPECT_DOUBLE_EQ(data[i][j], m.get(i, j));
//        }
//    }
//}

TEST(Vector, IO) {
    Vector v(100);
    for (size_t i = 0; i < 100; ++i) {
        v[i] = static_cast<double>(i);
    }
    ofstream fout("../tests/vector_io/vector.in");
    fout << v;
    fout.close();
    ifstream fin("../tests/vector_io/vector.in");
    Vector v1(100);
    fin >> v1;
    fin.close();
    for (size_t i = 0; i < 100; ++i) {
        EXPECT_DOUBLE_EQ(static_cast<double>(i), v1[i]);
    }
}

TEST(ProfileMatrix, In) {
    vector<vector<double>> data = {
            {1, 0, 0, 6, 0},
            {0, 2, 4, 6, 0},
            {0, 1, 3, 7, 0},
            {1, 2, 3, 4, 8},
            {0, 0, 0, 9, 5}
    };
    ifstream fin("../tests/matrix_io/matrix.in");
    ProfileMatrix m;
    fin >> m;
    for (size_t i = 0; i < m.rowsSize(); ++i) {
        for (size_t j = 0; j < m.rowsSize(); ++j) {
            EXPECT_DOUBLE_EQ(data[i][j], m.get(i, j));
        }
    }
}

TEST(ProfileMatrix, Out) {
    ProfileMatrix m;
    ifstream fin("../tests/matrix_io/matrix.in");
    fin >> m;
    ofstream fout("../tests/matrix_io/matrix.out");
    fout << m;
    fout.close();
    ifstream fin2("../tests/matrix_io/matrix.out");
    ProfileMatrix m2;
    fin2 >> m2;
    EXPECT_EQ(m.rowsSize(), m2.rowsSize());
    for (size_t i = 0; i < m.rowsSize(); ++i) {
        for (size_t j = 0; j < m.rowsSize(); ++j) {
            EXPECT_DOUBLE_EQ(m.get(i, j), m2.get(i, j));
        }
    }
}

TEST(RandomGenerator, Simple) {
    for (size_t i = 0; i < N_GEN; ++i) {
        generateRandom(i);
    }
}

TEST(RandomGenerator, Hard) {
    for (size_t i = 0; i < N_GEN; ++i) {
        generateSequence(i);
    }
}

TEST(RandomGenerator, Advanced) {
    vector<size_t> dims = {1, 2, 3, 5, 10, 25, 50, 100, 500, 1000};
    assert(dims.size() == N_GEN);
    for (int i = 0; i < N_GEN; ++i) {
        generateGilbert(dims[i], i);
    }
}

TEST(LUDecomposition, Simple) {
    vector<vector<double>> L = {
            {1, 0, 0,  0,  0},
            {0, 2, 0,  0,  0},
            {0, 1, 1,  0,  0},
            {1, 2, -1, -4, 0},
            {0, 0, 0,  9,  23}
    };
    vector<vector<double>> U = {
            {1, 0, 0, 6, 0},
            {0, 1, 2, 3, 0},
            {0, 0, 1, 4, 0},
            {0, 0, 0, 1, -2},
            {0, 0, 0, 0, 1}
    };
    ProfileMatrix m;
    ifstream fin("../tests/matrix_io/matrix.in");
    fin >> m;
    LUMatrix luM = toLU(m);
    for (size_t i = 0; i < m.rowsSize(); ++i) {
        for (size_t j = 0; j < m.rowsSize(); ++j) {
            EXPECT_DOUBLE_EQ(L[i][j], luM.getL(i, j));
            EXPECT_DOUBLE_EQ(U[i][j], luM.getU(i, j));
        }
    }
}

void LUDecomposition_Hard_iteration(const string &filename) {
    for (int i = 0; i < N_GEN; ++i) {
        ProfileMatrix m;
        string nn = filename + to_string(i) + ".txt";
        ifstream fin(filename + to_string(i) + ".txt");
        fin >> m;
        CanonicalMatrix canM = toCanonicalMatrix(m),
                canL(m.rowsSize(), vector<double>(m.rowsSize())),
                canU(m.rowsSize(), vector<double>(m.rowsSize()));
        LUMatrix luM = toLU(m);
        for (int j = 0; j < luM.size(); ++j) {
            for (int t = 0; t < luM.size(); ++t) {
                canL.set(j, t, luM.getL(j, t));
                canU.set(j, t, luM.getU(j, t));
            }
        }
        for (int j = 0; j < canM.rowsSize(); ++j) {
            for (int t = 0; t < canM.rowsSize(); ++t) {
                double tmp = 0;
                for (int s = 0; s < canM.rowsSize(); ++s) {
                    tmp += canL.get(j, s) * canU.get(s, t);
                }
                if (abs(tmp - canM.get(j, t)) > 1e-6) {
                    EXPECT_DOUBLE_EQ(tmp, canM.get(j, t));
                }
            }
        }
    }
}

/*  Они проходят, но долго, потому что я перемножаю за N^3 для N ~ 10^3
TEST(LUDecomposition, Hard) {
    LUDecomposition_Hard_iteration("../tests/matrix_io/matrix_");
    LUDecomposition_Hard_iteration("../tests/matrix_io/matrix_seq_");
    LUDecomposition_Hard_iteration("../tests/matrix_io/matrix_gil_");
}*/

bool zero(const Vector &v, double eps) {
    return all_of(v.begin(), v.end(), [eps](double el) { return el < eps; });
}

TEST(Gauss, RunMethod10Dim) {
//    for (size_t i = 0; i < 1; ++i) {
//        generateRandom(10, 3);
//        ifstream finMatrix("../tests/matrix_io/matrix_10.txt");
//        ifstream finVector("../tests/vector_io/vector_10.txt");
//        ProfileMatrix A;
//        Vector b(3);
//        finMatrix >> A;
//        finVector >> b;
//        ProfileMatrix A1 = A;
//        Vector b1 = b;
//        Vector b2 = b;
//        CanonicalMatrix slowMatrix = A.toCanonicalFormat();
//        Vector x = solveWithLeadingElement(A, b);
//        Vector x1 = solveLU(A1, b1);
//        auto b_ = slowMatrix * x;
//        auto b_1 = slowMatrix * x1;
//        EXPECT_TRUE(zero(b_ - b2, 0.001));
//        EXPECT_TRUE(zero(b_1 - b2, 0.001));
//    }
//    solveLUGauss("../tests/matrix_io/matrix_0.txt",
  //               "../tests/vector_io/vector_0.txt",
    //             "../tests/results_io/result_0.txt");
}

void Gauss_Advanced_iteration(const string &filename_m, const string &filename_v) {
    for (int i = 0; i < N_GEN; ++i) {
        ProfileMatrix m;
        ifstream fin_m(filename_m + to_string(i) + ".txt");
        fin_m >> m;
        Vector b(m.rowsSize());
        ifstream fin_v(filename_v + to_string(i) + ".txt");
        fin_v >> b;
        ProfileMatrix m1 = m;
        Vector b1 = b;
        Vector b2 = b;
        CanonicalMatrix sm = toCanonicalMatrix(m);
        Vector x = solveLeadingElementGauss(m, b);
        Vector x1 = solveLUGauss(m1, b1);
        Vector b_ = sm * x;
        Vector b_1 = sm * x1;
        for (int j = 0; j < b1.size(); ++j) {
            if (abs(b_[j] - b2[j]) > 10) {
                EXPECT_DOUBLE_EQ(b_[j], b2[j]);
            }
            if (abs(b_1[j] - b2[j]) > 10) {
                EXPECT_DOUBLE_EQ(b_1[j], b2[j]);
            }
        }
    }
}

TEST(Gauss, Advanced) {
    //Gauss_Advanced_iteration("../tests/matrix_io/matrix_", "../tests/vector_io/vector_");
    //Gauss_Advanced_iteration("../tests/matrix_io/matrix_seq_", "../tests/vector_io/vector_seq_");
    //Gauss_Advanced_iteration("../tests/matrix_io/matrix_gil_", "../tests/vector_io/vector_gil_");
}

TEST(SparseMatrix, Simple) {
    vector<vector<double>> data = {
            {1, 0,  0,  2},
            {0, 5,  9,  0},
            {0, -4, -1, 8},
            {3, 0,  4,  5}
    };
    SparseMatrix m(data);
    EXPECT_DOUBLE_EQ(m.rowsSize(), data.size());
    for (int i = 0; i < m.rowsSize(); ++i) {
        EXPECT_DOUBLE_EQ(m.diagonal[i], data[i][i]);
    }
    vector<size_t> ex_pr = {0, 0, 0, 1, 3};
    EXPECT_DOUBLE_EQ(m.profile.size(), ex_pr.size());
    for (int i = 0; i < ex_pr.size(); ++i) {
        EXPECT_DOUBLE_EQ(m.profile[i], ex_pr[i]);
    }
    vector<double> ex_row = {-4, 3, 4};
    EXPECT_DOUBLE_EQ(m.rowElements.size(), ex_row.size());
    for (int i = 0; i < ex_row.size(); ++i) {
        EXPECT_DOUBLE_EQ(m.rowElements[i], ex_row[i]);
    }
    vector<double> ex_col = {9, 2, 8};
    EXPECT_DOUBLE_EQ(m.colElements.size(), ex_col.size());
    for (int i = 0; i < ex_col.size(); ++i) {
        EXPECT_DOUBLE_EQ(m.colElements[i], ex_col[i]);
    }
    vector<size_t> ex_num = {1, 0, 2};
    EXPECT_DOUBLE_EQ(m.colNumber.size(), ex_num.size());
    for (int i = 0; i < ex_num.size(); ++i) {
        EXPECT_DOUBLE_EQ(m.colNumber[i], ex_num[i]);
    }
}

TEST(SparseMatrix, Evil) {
    for (int i = 0; i < N_GEN; ++i) {
        generateExtraRandom(i);
    }
}

TEST(ProfileMatrix, FuckingAdvanced) {
    for (size_t k = 0; k < 10; ++k) {
        std::random_device rd;
        std::mt19937 gen{rd()};
        vector<vector<double>> data(1000, vector<double>(1000));
        for (size_t i = 0; i < 1000; ++i) {
            for (size_t j = 0; j <= i; ++j) {
                data[i][j] = data[j][i] = abs(((int) gen())) % 5;
            }
        }
        SparseMatrix A(data);
        for (size_t i = 0; i < A.rowsSize(); ++i) {
            for (size_t j = 0; j < A.rowsSize(); ++j) {
                if (A.get(i, j) != data[i][j]) {
                    cout << 1;
                }
                EXPECT_DOUBLE_EQ(A.get(i, j), data[i][j]);
            }
        }
    }
}

TEST(GaussGrad, Simple) {
    for (size_t i = 0; i < N_GEN; ++i) {
        generateExtraRandom(0, 3);
        ifstream finMatrix("../tests/matrix_io/extra_matrix_0.txt");
        ifstream finVector("../tests/vector_io/extra_vector_0.txt");
        SparseMatrix A;
        Vector b(3);
        finMatrix >> A;
        finVector >> b;
        Vector x0 = {1, 1, 10};
        Vector x = solveConjGrad(A, b, x0, 0.001);
        Vector b1 = A * x;
        EXPECT_TRUE(zero(b - b1, 0.1));
    }
}

void Conj_Gauss_Advanced_iteration(const string &filename_m, const string &filename_v) {
    for (int i = 0; i < N_GEN; ++i) {
        SparseMatrix m;
        ifstream fin_m(filename_m + to_string(i) + ".txt");
        fin_m >> m;
        Vector b(m.rowsSize());
        ifstream fin_v(filename_v + to_string(i) + ".txt");
        fin_v >> b;
        Vector b2 = b;
        CanonicalMatrix sm = toCanonicalMatrix(m);
        vector<double> x0(m.rowsSize());
        Vector x = solveConjGrad(m, b, x0, 1);
        Vector b_ = sm * x;
        for (int j = 0; j < b.size(); ++j) {
            if (abs(b_[j] - b2[j]) > 10) {
                EXPECT_DOUBLE_EQ(b_[j], b2[j]);
            }
        }
    }
}

TEST(GaussGrad, Advanced) {
    Conj_Gauss_Advanced_iteration("../tests/matrix_io/extra_matrix_", "../tests/vector_io/extra_vector_");
}

TEST(Seq, Info) {
    for (int i = 0; i < N_GEN; ++i) {
        ProfileMatrix m, cpm;
        ifstream fin_m("../tests/matrix_io/matrix_seq_" + to_string(i) + ".txt");
        fin_m >> m;
        cpm = m;
        Vector b0(m.rowsSize()), cpb0;
        ifstream fin_v("../tests/vector_io/vector_seq_" + to_string(i) + ".txt");
        fin_v >> b0;
        cpb0 = b0;
        Vector x0(m.rowsSize()), cpx0;
        for (size_t j = 0; j < m.rowsSize(); ++j) {
            x0[j] = j + 1;
        }
        cpx0 = x0;

        Vector x = solveLUGauss(m, b0);
        double diff_x = norm(x - cpx0);
        double diff_b = norm(cpb0 - cpm * x);
        double n_x = norm(cpx0);
        double n_b = norm(cpb0);
        cout << fixed << setprecision(20) << "cond = " <<
             ((diff_b * n_x) == 0 ? 1 : (diff_x * n_b) / (diff_b * n_x)) <<
             ", delta x = " << diff_x <<
             ", delta x / norm x = " << (n_x == 0 ? 0 : diff_x / n_x) << endl;
    }
}

TEST(Gil, Info) {
    for (int i = 0; i < N_GEN; ++i) {
        ProfileMatrix m, cpm;
        ifstream fin_m("../tests/matrix_io/matrix_gil_" + to_string(i) + ".txt");
        fin_m >> m;
        cpm = m;
        Vector b0(m.rowsSize()), cpb0;
        ifstream fin_v("../tests/vector_io/vector_gil_" + to_string(i) + ".txt");
        fin_v >> b0;
        cpb0 = b0;
        Vector x0(m.rowsSize()), cpx0;
        for (size_t j = 0; j < m.rowsSize(); ++j) {
            x0[j] = j + 1;
        }
        cpx0 = x0;
        Vector x = solveLUGauss(m, b0);
        double diff_x = norm(x - cpx0);
        double diff_b = norm(cpb0 - cpm * x);
        double n_x = norm(cpx0);
        double n_b = norm(cpb0);
        cout << fixed << setprecision(20) << "cond = " <<
             ((diff_b * n_x) == 0 ? 1 : (diff_x * n_b) / (diff_b * n_x)) <<
             ", delta x = " << diff_x <<
             ", delta x / norm x = " << (n_x == 0 ? 0 : diff_x / n_x) << endl;
    }
}

TEST(Bonus, FistTask) {
    const int DIM = 100;
    Vector x0(DIM, 0);
    std::vector<std::vector<double>> table;
    for (size_t testId = 0; testId < 20; ++testId) {
        Vector x_ = generateVectorOfSize(DIM);
        generateRandomBonus(testId, x_);

        solveConjGrad(A_FILE(DIM, testId),
                      B_FILE(DIM, testId),
                      X_FILE(DIM, testId),
                      DATA_FILE(DIM, testId),
                      x0, 1e-7);

        SparseMatrix A = readFromFile<SparseMatrix>(A_FILE(DIM, testId));
        Vector b = readFromFile(DIM, B_FILE(DIM, testId));
        Vector x = readFromFile(DIM, X_FILE(DIM, testId));
        EvalData evalData = readFromFile<EvalData>(DATA_FILE(DIM, testId));

        table.push_back({(double) evalData.iterationsNumber, absError(x, x_), relativeError(x, x_), cond(A, b, x, x_)});
    }
    cerr << toLatexTable(table);
}

TEST(Bonus, SecondTask) {
    const int DIM = 10;
    Vector x0(DIM, 0);
    std::vector<std::vector<double>> table;
    for (size_t testId = 0; testId < 5; ++testId) {
        Vector x_ = generateVectorOfSize(DIM);
        generateBonusSequence(testId, x_);

        solveConjGrad(A_FILE_SEQ(DIM, testId),
                      B_FILE_SEQ(DIM, testId),
                      X_FILE_SEQ(DIM, testId),
                      DATA_FILE_SEQ(DIM, testId),
                      x0, 1e-7);

        SparseMatrix A = readFromFile<SparseMatrix>(A_FILE_SEQ(DIM, testId));
        Vector b = readFromFile(DIM, B_FILE_SEQ(DIM, testId));
        Vector x = readFromFile(DIM, X_FILE_SEQ(DIM, testId));
        EvalData evalData = readFromFile<EvalData>(DATA_FILE_SEQ(DIM, testId));

        table.push_back({(double) evalData.iterationsNumber, absError(x, x_), relativeError(x, x_), cond(A, b, x, x_)});
    }
    cerr << toLatexTable(table);
}

TEST(Bonus, ForthTask) {
    const int DIM = 100;
    Vector x0(DIM, 0);
    std::vector<std::vector<double>> table;
    for (size_t testId = 0; testId < 5; ++testId) {
        Vector x_ = generateVectorOfSize(DIM);
        generateBonusGilbert(testId, x_);

        solveConjGrad(A_FILE_GIL(DIM, testId),
                      B_FILE_GIL(DIM, testId),
                      X_FILE_GIL(DIM, testId),
                      DATA_FILE_GIL(DIM, testId),
                      x0, 1e-7);

        SparseMatrix A = readFromFile<SparseMatrix>(A_FILE_GIL(DIM, testId));
        Vector b = readFromFile(DIM, B_FILE_GIL(DIM, testId));
        Vector x = readFromFile(DIM, X_FILE_GIL(DIM, testId));
        EvalData evalData = readFromFile<EvalData>(DATA_FILE_GIL(DIM, testId));

        table.push_back({(double) evalData.iterationsNumber, absError(x, x_), relativeError(x, x_), cond(A, b, x, x_)});
    }
    cerr << toLatexTable(table);
}
