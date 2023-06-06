#include "mainwindow.h"
#include "ufo/unidimensional_function_optimization.h"

#include <QApplication>
#include <cmath>

namespace ufo = unidimensional_function_optimization;

int main(int argc, char *argv[])
{
    ufo::to_eval sample = {
            [](double x){ return x - log(x); },
            {0.5, 4.},
            0.001
    };

    ufo::to_eval sample1 = {
            [](double x) { return -log(x * x - exp(x) / log(2 * x) + sqrt(x)); },
            {2, 2.75},
            0.001
    };

    ufo::to_eval sample2 = {
            [](double x) { return log(x - 2) * log(x - 2) + log(10 - x) * log(10 - x) - pow(x, 0.2); },
            {6., 9.9},
            0.001
    };

    QApplication a(argc, argv);
    MainWindow w(sample2);
    w.show();
    return a.exec();
}
