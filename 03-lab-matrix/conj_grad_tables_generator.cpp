#include "LinearSystem.h"
#include "new_generators.h"
#include "latex_tools.h"

using namespace std;

latex_line_data_t run(const data_t &data) {
    size_t n = data.size();
    SparseMatrix A = data, ACopy = A;
    Vector xTrue = randomVector(n);
    Vector b = fromSolution(data, xTrue), bCopy = b;
    Vector xStart = Vector(n, 0);
    EvalData evalData;
    Vector x = solveConjGradLogging(ACopy, bCopy, xStart, 1e-10, evalData);

    return dataLine(n, A, b, xTrue, x, evalData);
}

void runRandom() {
    latex_table_data_t tableData;
    vector<size_t> dims = {1000};
    for (size_t n : dims) {
        tableData.push_back(run(randomSymData(n)));
    }
    writeTo("../bonus_tables", "random.txt", toLatexTable(tableData));
    cerr << "runRandom done\n";
}

void runSeq() {
    latex_table_data_t tableData;
    vector<size_t> dims = {10, 20, 50, 100, 150, 200, 300, 500, 700, 1000};
    for (size_t n : dims) {
        data_t data = randomRawSymSeqData(n);
        for (size_t k = 0; k < 1; ++k) {
            data_t dataDominanced = addDominance(data, k);
            tableData.push_back(run(dataDominanced));
        }
    }
    writeTo("../bonus_tables", "seq.txt", toLatexTable(tableData));
    cerr << "runSeq done\n";
}

void runInvSeq() {
    latex_table_data_t tableData;
    vector<size_t> dims = {10, 20, 50, 100, 150, 200, 300, 500, 700, 1000};
    for (size_t n : dims) {
        data_t data = invSeq(randomRawSymSeqData(n));
        for (size_t k = 0; k < 1; ++k) {
            data_t dataDominanced = addDominance(data, k);
            tableData.push_back(run(dataDominanced));
        }
    }
    writeTo("../bonus_tables", "inv_seq.txt", toLatexTable(tableData));
    cerr << "runInvSeq done\n";
}

void runGil() {
    latex_table_data_t tableData;
    vector<size_t> dims = {10, 20, 50, 100, 150, 200, 300, 500, 700, 1000};
    for (size_t n : dims) {
        tableData.push_back(run(randomGilData(n)));
    }
    writeTo("../bonus_tables", "gil.txt", toLatexTable(tableData));
    cerr << "runGil done\n";
}

int main() {
//    runRandom();
    runSeq();
//    runInvSeq();
//    runGil();
    return 0;
}