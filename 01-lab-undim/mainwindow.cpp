#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qcustomplot/qcustomplot.h"

#include <cmath>

MainWindow::MainWindow(ufo::to_eval sample, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), sample_f(sample.f), sample_seg(sample.seg),
          data({sample.eval(ufo::dichotomy_method), sample.eval(ufo::golden_section_method),
                sample.eval(ufo::fiboncci_method), sample.eval(ufo::parabola_method),
                sample.eval(ufo::brents_method)}) {
    ui->setupUi(this);
    ui->customPlot->setInteraction(QCP::iRangeZoom, true);
    this->setFixedSize(QSize(1220, 750));

    funcGraph(sample_f, sample.seg);
    auto f = [](double x) { return (x - 2) * (x - 3) + 1; };
    funcGraph(f, {0., 4.}, Qt::red);

    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    iteration();

    ui->customPlot->replot();

    connect(ui->nextButton, &QPushButton::released, this, &MainWindow::showNextIteration);
    connect(ui->prevButton, &QPushButton::released, this, &MainWindow::showPrevIteration);
    connectMethodButtons();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::funcGraph(const ufo::func_t &f, const ufo::segment &seg, const QColor &color) {
    QVector<double> x(1001), y(1001);
    for (int i = 0; i <= 1000; ++i) {
        x[i] = seg.a + i * ((seg.b - seg.a) / 1000);
        y[i] = f(x[i]);
    }
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setData(x, y);
    ui->customPlot->graph()->setPen(color);
}

void MainWindow::point(double x, double y, const QColor &color) {
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setPen(color);
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsImpulse);
    ui->customPlot->graph()->setData({x}, {y});
}


void MainWindow::iteration() {
    if (method_num == 3) {
        parabola_iteration();
        return;
    }
    clearAllExceptGraph();
    auto iteration = data[method_num].iterations[it_num];
    for (size_t i = 0; i < iteration.xs.size(); ++i) {
        point(iteration.xs[i],
              iteration.fs[i], Qt::green);
    }
    point(iteration.a,
          sample_f(iteration.a));
    point(iteration.b,
          sample_f(iteration.b));
}

void MainWindow::parabola_iteration() {
    auto iteration = data[method_num].iterations[it_num];
    if (iteration.xs.size() == 3) {
        clearAllExceptGraph();
        double x1 = iteration.xs[0];
        double x2 = iteration.xs[1];
        double x3 = iteration.xs[2];

        double f1 = sample_f(x1);
        double f2 = sample_f(x2);
        double f3 = sample_f(x3);

        double a0 = f1;
        double a1 = (f2 - f1) / (x2 - x1);
        double a2 = ((f3 - f1) / (x3 - x1) - (f2 - f1) / (x2 - x1)) / (x3 - x2);

        funcGraph([=](double x) { return a0 + a1 * (x - x1) + a2 * (x - x1) * (x - x2); }, sample_seg, Qt::red);
        if (it_num == 0) {
            point(x1, f1, Qt::green);
            point(x2, f2, Qt::green);
            point(x3, f3, Qt::green);
        }
    } else {
        if (it_num == 1) {
            ui->customPlot->graph(ui->customPlot->graphCount() - 1)->data()->clear();
            ui->customPlot->graph(ui->customPlot->graphCount() - 2)->data()->clear();
            ui->customPlot->graph(ui->customPlot->graphCount() - 3)->data()->clear();
        }
        point(iteration.xs[0], iteration.fs[0], Qt::green);
    }
}

void MainWindow::showPrevIteration() {
    if (it_num == 0) {
        return;
    }
    --it_num;
    iteration();
    ui->customPlot->replot();
}

void MainWindow::showNextIteration() {
    if (it_num + 1 == data[method_num].iterations.size()) {
        return;
    }
    ++it_num;
    iteration();
    ui->customPlot->replot();
}

void MainWindow::clearAllExceptGraph() {
    for (size_t i = 1; i < ui->customPlot->graphCount(); ++i) {
        ui->customPlot->graph(i)->data()->clear();
    }
}

void MainWindow::setMethodAndShow(size_t num) {
    clearAllExceptGraph();
    method_num = num;
    it_num = 0;
    iteration();
    ui->customPlot->replot();
}

void MainWindow::connectMethodButtons() {
    buttons = {ui->dichoButton, ui->goldenButton, ui->fibButton, ui->paraButton, ui->brentsButton};
    for (size_t i = 0; i < 5; ++i) {
        connect(buttons[i], &QPushButton::released, [this,i]() { this->setMethodAndShow(i); });
    }
}