#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Test {
    string in;
    string out;
    string cert;
};

vector<Test> tests = {
        {"test1.in", "test1.out", "test1.cert"},
        {"test2.in", "test2.out", "test2.cert"},
        {"test3.in", "test3.out", "test3.cert"},
};

int main() {
    for (auto &test : tests) {

        // run calculation

        ifstream in(test.in);
        ifstream out(test.out);
        ifstream cert(test.cert);

        // compare output with cert
    }
    return 0;
}

