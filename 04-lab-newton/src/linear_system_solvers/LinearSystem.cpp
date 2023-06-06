#include "LinearSystem.h"

struct LUGaussSolver {
    LUGaussSolver(Matrix &A, Vector &b) : lu(toLU(A).matrix), b(&b) {}

    Vector solve() {
        forward();
        backward();
        return (*b);
    }

    // Solves Ly = b. Solution in b.
    void forward() {
        for (size_t j = 0; j < size(); ++j) {
            normalize(j);
            for (size_t i = j + 1; i < size(); ++i) {
                lineDifference(j, i, j);
            }
        }
    }

    // Solves Ux = y.
    void backward() {
        for (ssize_t j = static_cast<ssize_t>(size()) - 1; j >= 0; --j) {
            for (ssize_t i = j - 1; i >= 0; --i) {
                lineDifference(j, i, j);
            }
        }
    }

    size_t size() const {
        return lu->rowsSize();
    }

    void normalize(size_t j) {
        double divider = lu->get(j, j);
        lu->set(j, j, 1);
        (*b)[j] /= divider;
    }

    void lineDifference(size_t iSubtrahend, size_t iMinuend, size_t j) {
        double factor = lu->get(iMinuend, j) / lu->get(iSubtrahend, j);
        lu->set(iMinuend, j, 0);
        (*b)[iMinuend] -= factor * (*b)[iSubtrahend];
    }

    Matrix *lu;
    Vector *b;
};

Vector solveLUGauss(Matrix &A, Vector &b) {
    return LUGaussSolver(A, b).solve();
}

void solveLUGauss(const std::string &fileA, const std::string &fileB, const std::string &fileRes) {
    std::ifstream finA(fileA);
    std::ifstream finB(fileB);
    std::ofstream foutRes(fileRes);
    ProfileMatrix A;
    finA >> A;
    Vector b(A.rowsSize());
    finB >> b;
    Vector res = solveLUGauss(A, b);
    foutRes << res;
}

struct LUGaussSolver2 {
    LUGaussSolver2(Matrix &A, Vector &b) : lu(toLU(A).matrix), b(&b) {}

    Vector solve() {
        Vector x = forward();
        x = backward(x);
        return x;
    }

    Vector forward() const {
        Vector x(size(), 0);
        for (int i = 0; i < size(); ++i) {
            double tmp = (*b)[i];
            for (int j = 0; j < i; ++j) {
                tmp -= lu->get(i, j) * x[j];
            }
            x[i] = tmp / lu->get(i, i);
        }
        return x;
    }

    Vector backward(const Vector &y) {
        Vector x(size(), 0);
        for (int i = (int) size() - 1; i >= 0; --i) {
            double tmp = y[i];
            for (int j = i + 1; j < size(); ++j) {
                tmp -= lu->get(i, j) * x[j];
            }
            x[i] = tmp;
        }
        return x;
    }

    size_t size() const {
        return lu->rowsSize();
    }

    Matrix *lu;
    Vector *b;
};

Vector solveLUGauss2(Matrix &A, Vector &b) {
    return LUGaussSolver2(A, b).solve();
}

struct LeadingElementGaussSolver {
    LeadingElementGaussSolver(Matrix &A, Vector &b) : A(&A), b(&b), perm(size()) {
        for (size_t i = 0; i < size(); ++i) {
            perm[i] = i;
        }
    }

    Vector solve() {
        forward();
        backward();
        unpermute();
        return *b;
    }

    void forward() {
        for (size_t j = 0; j < size(); ++j) {
            std::swap(perm[j], perm[getLeading(j)]);
            for (size_t i = j + 1; i < size(); ++i) {
                forwardLineDiff(j, i, j);
            }
            normalize(j);
        }
    }

    void backward() {
        for (ssize_t j = static_cast<ssize_t>(size()) - 1; j >= 0; --j) {
            for (ssize_t i = j - 1; i >= 0; --i) {
                backwardLineDiff(j, i, j);
            }
        }
    }

    size_t size() const {
        return A->rowsSize();
    }

    size_t getLeading(size_t j) {
        size_t iMax = j;
        for (size_t i = j + 1; i < size(); ++i) {
            if (std::abs(A->get(perm[iMax], j)) < std::abs(A->get(perm[i], j))) {
                iMax = i;
            }
        }
        return iMax;
    }

    void normalize(size_t j) {
        size_t i = perm[j];
        double divider = A->get(i, j);
        for (size_t j1 = j; j1 < size(); ++j1) {
            A->set(i, j1, A->get(i, j1) / divider);
        }
        (*b)[i] /= divider;
    }

    void forwardLineDiff(size_t iSubtrahend, size_t iMinuend, size_t j) {
        iSubtrahend = perm[iSubtrahend];
        iMinuend = perm[iMinuend];
        double factor = A->get(iMinuend, j) / A->get(iSubtrahend, j);
        for (size_t j1 = j; j1 < size(); ++j1) {
            A->set(iMinuend, j1, A->get(iMinuend, j1) - factor * A->get(iSubtrahend, j1));
        }
        (*b)[iMinuend] -= factor * (*b)[iSubtrahend];
    }

    void backwardLineDiff(size_t iSubtrahend, size_t iMinuend, size_t j) {
        iSubtrahend = perm[iSubtrahend];
        iMinuend = perm[iMinuend];
        double factor = A->get(iMinuend, j) / A->get(iSubtrahend, j);
        A->set(iMinuend, j, A->get(iMinuend, j) - factor * A->get(iSubtrahend, j));
        (*b)[iMinuend] -= factor * (*b)[iSubtrahend];
    }

    void unpermute() {
        Vector unpermutedB(size());
        for (size_t i = 0; i < size(); ++i) {
            unpermutedB[i] = (*b)[perm[i]];
        }
        *b = unpermutedB;
    }

    Matrix *A;
    Vector *b;
    std::vector<size_t> perm;
};

Vector solveLeadingElementGauss(Matrix &A, Vector &b) {
    return LeadingElementGaussSolver(A, b).solve();
}

void solveLeadingElementGauss(const std::string &fileA, const std::string &fileB, const std::string &fileRes) {
    std::ifstream finA(fileA);
    std::ifstream finB(fileB);
    std::ofstream foutRes(fileRes);
    ProfileMatrix A;
    finA >> A;
    Vector b(A.rowsSize());
    finB >> b;
    Vector res = solveLeadingElementGauss(A, b);
    foutRes << res;
}

Vector solveConjGrad(const Matrix &A, Vector &b, Vector &x0, double eps) {
    Vector rPrev = b - A * x0;
    Vector zPrev = rPrev;
    Vector xPrev = x0;
    while (norm(rPrev) > eps * norm(b)) {
        double alphaCur = (rPrev * rPrev) / ((A * zPrev) * zPrev);
        Vector xCur = xPrev + alphaCur * zPrev;
        Vector rCur = rPrev - alphaCur * (A * zPrev);
        double betaCur = (rCur * rCur) / (rPrev * rPrev);
        Vector zCur = rCur + betaCur * zPrev;

        rPrev = rCur;
        zPrev = zCur;
        xPrev = xCur;
    }
    return xPrev;
}

Vector solveConjGradLogging(const Matrix &A, Vector &b, Vector &x0, double eps, EvalData &data) {
    data.iterationsNumber = 0;

    Vector rPrev = b - A * x0;
    Vector zPrev = rPrev;
    Vector xPrev = x0;
    while (norm(rPrev) > eps * norm(b) && data.iterationsNumber < 1e5) {
        ++data.iterationsNumber;

        double scalarPrev = rPrev * rPrev;
        Vector AzPrev = A * zPrev;

        double alphaCur = scalarPrev / (AzPrev * zPrev);
        Vector xCur = xPrev + alphaCur * zPrev;
        Vector rCur = rPrev - alphaCur * AzPrev;
        double betaCur = (rCur * rCur) / scalarPrev;

        if (data.iterationsNumber == A.rowsSize()) {
            betaCur = 0;
        }

        Vector zCur = rCur + betaCur * zPrev;

        rPrev = rCur;
        zPrev = zCur;
        xPrev = xCur;
    }
    return xPrev;
}

void solveConjGrad(const std::string &fileA,
                   const std::string &fileB,
                   const std::string &fileRes,
                   const std::string &fileData,
                   Vector &x0, double eps) {
    std::ifstream finA(fileA);
    std::ifstream finB(fileB);
    std::ofstream foutRes(fileRes);
    std::ofstream foutData(fileData);
    SparseMatrix A;
    finA >> A;
    Vector b(A.rowsSize());
    finB >> b;
    EvalData data;
    Vector res = solveConjGradLogging(A, b, x0, eps, data);
    foutRes << res;
    foutData << data;
}
