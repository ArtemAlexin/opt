#include "LinearSystem.h"
#include "new_generators.h"
#include "latex_tools.h"

using namespace std;

latex_line_data_t run(const data_t &data) {
    size_t n = data.size();
    ProfileMatrix A = data, ACopy = A;
    Vector xTrue = Vector(n, 0);
    for (size_t i = 0; i < n; ++i) {
        xTrue[i] = i + 1;
    }
    Vector b = fromSolution(data, xTrue), bCopy = b;
    EvalData evalData;
    Vector x = solveLeadingElementGauss(ACopy, bCopy);
    return dataLine(n, A, b, xTrue, x, evalData);
}

void runRandom() {
    latex_table_data_t tableData;
    vector<size_t> dims = {10, 20};
    for (size_t n : dims) {
        tableData.push_back(run(randomSymData(n)));
    }
    writeTo("../leading_tables", "random.txt", toLatexTable(tableData));
    cerr << "runRandom done\n";
}

void runSeq() {
    latex_table_data_t tableData;
    vector<size_t> dims = {10, 20, 50, 100, 200};
    for (size_t n : dims) {
        data_t data = randomRawSymSeqData(n);
        for (size_t k = 0; k < 10; ++k) {
            data_t dataDominanced = addDominance(data, k);
            tableData.push_back(run(dataDominanced));
        }
    }
    writeTo("../leading_tables", "seq.txt", toLatexTable(tableData));
    cerr << "runSeq done\n";
}

void runInvSeq() {
    latex_table_data_t tableData;
    vector<size_t> dims = {10, 20, 50, 100, 200};
    for (size_t n : dims) {
        data_t data = invSeq(randomRawSymSeqData(n));
        for (size_t k = 0; k < 10; ++k) {
            data_t dataDominanced = addDominance(data, k);
            tableData.push_back(run(dataDominanced));
        }
    }
    writeTo("../leading_tables", "inv_seq.txt", toLatexTable(tableData));
    cerr << "runInvSeq done\n";
}

void runGil() {
    latex_table_data_t tableData;
    vector<size_t> dims = {10, 20, 50, 100, 150, 200, 300, 500, 700, 1000};
    for (size_t n : dims) {
        tableData.push_back(run(randomGilData(n)));
    }
    writeTo("../leading_tables", "gil.txt", toLatexTable(tableData));
    cerr << "runGil done\n";
}

int main() {
//    runRandom();
//    runSeq();
//    runInvSeq();
    runGil();
    return 0;
}