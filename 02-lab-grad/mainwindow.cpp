#include <qcustomplot/qcustomplot.h>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "generator/generate_stat.h"


// Hardcoded function to be explored and unidimensional method
grad::quad_function FUNCTION = {
        {{608, 506},
         {506, 608}},
        {50, 130},
        -111
};

ufo::method_t UNDIM_METHOD = ufo::golden_section_method;


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), current_iteration(0) {
    ui->setupUi(this);
    ui->graphField->setInteraction(QCP::iRangeZoom, true);
    this->setFixedSize(QSize(1385, 840));

    init_eps_x();
    init_methods();
    init_axis();
    init_plot();

//    plot_stat(5);
}

void MainWindow::init_eps_x() {
//    ui->epsLineEdit->setValidator(new QDoubleValidator(this));
//    ui->x1LineEdit->setValidator(new QDoubleValidator(this));
//    ui->x2LineEdit->setValidator(new QDoubleValidator(this));
}

void MainWindow::init_methods() {
    connect(ui->gradButtom, &QPushButton::released, this, [&]() { start_method(0); });
    connect(ui->quickGradButton, &QPushButton::released, this, [&]() { start_method(1); });
    connect(ui->conjGradButton, &QPushButton::released, this, [&]() { start_method(2); });

    connect(ui->nextButton, &QPushButton::released, this, &MainWindow::next);
    connect(ui->prevButton, &QPushButton::released, this, &MainWindow::prev);
}

void MainWindow::init_axis() const {
    ui->graphField->yAxis->setRange(-50, 50);
    ui->graphField->xAxis->setRange(-75, 75);
    ui->graphField->yAxis->setVisible(ui->axiesCheckBox->isChecked());
    ui->graphField->xAxis->setVisible(ui->axiesCheckBox->isChecked());
    connect(ui->axiesCheckBox, &QCheckBox::stateChanged,
            ui->graphField, [&](int state) {
                ui->graphField->xAxis->setVisible(state);
                ui->graphField->yAxis->setVisible(state);
                ui->graphField->replot();
            });
    connect(ui->axiesLabelsCheckBox, &QCheckBox::stateChanged,
            ui->graphField, [&](int state) {
                ui->graphField->xAxis->setLabel(state ? "x" : "");
                ui->graphField->yAxis->setLabel(state ? "y" : "");
                ui->graphField->replot();
            });
    ui->axiesCheckBox->setCheckState(Qt::Checked);
    ui->axiesLabelsCheckBox->setCheckState(Qt::Checked);
}

void MainWindow::init_plot() {
    data = METHODS[0](FUNCTION, {0, 0}, 0.001, UNDIM_METHOD);
    curve = new QCPCurve(ui->graphField->xAxis, ui->graphField->yAxis);
    plot_level_curves();
    show_iteration(true);
    show_iteration(false);

    ui->levelLinesCheckBox->setCheckState(Qt::Checked);
    connect(ui->levelLinesCheckBox, &QCheckBox::stateChanged, this, [&](int state){
        if (state) {
            for (auto* p : levelCurves) {
                p->data()->clear();
            }
            plot_level_curves();
        } else {
            for (auto* p : levelCurves) {
                p->data()->clear();
            }
        }
        ui->graphField->replot();
    });
}

std::pair<double, double> solve_quad_equation(double A, double B, double C) {
    return {(-B - sqrt(B * B - 4 * A * C)) / (2 * A), (-B + sqrt(B * B - 4 * A * C)) / (2 * A)};
}

std::pair<double, double> calc_interval(double level) {
    double A = FUNCTION.A[0][1] * FUNCTION.A[0][1] - FUNCTION.A[0][0] * FUNCTION.A[1][1];
    double B = 2 * FUNCTION.A[0][1] * FUNCTION.B[1] - 2 * FUNCTION.A[1][1] * FUNCTION.B[0];
    double C = FUNCTION.B[1] * FUNCTION.B[1] - 2 * FUNCTION.A[1][1] * FUNCTION.C + 2 * FUNCTION.A[1][1] * level;
    auto solution = solve_quad_equation(A, B, C);
    if (solution.first > solution.second) {
        std::swap(solution.first, solution.second);
    }
    double len = solution.second - solution.first;
    return {solution.first + len / 1000, solution.second - len / 1000};
}

vector_t calc_y(double x, double level) {
//    double A = 0.5 * FUNCTION.A[0][0];
//    double B = FUNCTION.A[0][1] * x + FUNCTION.B[1];
//    double C = 0.5 * FUNCTION.A[1][1] * x * x + FUNCTION.B[0] * x + FUNCTION.C - level;
    double A = 0.5 * FUNCTION.A[1][1];
    double B = FUNCTION.A[0][1] * x + FUNCTION.B[1];
    double C = 0.5 * FUNCTION.A[0][0] * x * x + FUNCTION.B[0] * x + FUNCTION.C - level;
    auto ys = solve_quad_equation(A, B, C);
    return {ys.first, ys.second};
}

void MainWindow::plot_level_curve(double level, int32_t n) {
    QVector<QCPCurveData> curveData;

    auto interval = calc_interval(level);
    double interval_len = interval.second - interval.first;
    double h = interval_len / n;

    double x = interval.first;
    for (int32_t i = 0; i < n; ++i) {
        double y = calc_y(x, level)[0];
        if (y == y) {
            curveData.append(QCPCurveData(i, x, y));
        }
        x += h;
    }
    x -= h;
    for (int32_t i = 0; i < n; ++i) {
        double y = calc_y(x, level)[1];
        if (y == y) {
            curveData.append(QCPCurveData(n + i, x, y));
        }
        x -= h;
    }
    curveData.append(QCPCurveData(2 * n, interval.first, calc_y(interval.first, level)[0]));
    QCPCurve *curve = new QCPCurve(ui->graphField->xAxis, ui->graphField->yAxis);
    curve->setBrush(QBrush(QColor(0, 0, 255, 20)));
    curve->data()->set(curveData);
    levelCurves.push_back(curve);
}

void MainWindow::plot_level_curves() {
    vector_t x_min = data.back();
    double y_min = FUNCTION.calc(x_min);

    for (double level = y_min; level < y_min + 1000; level += 100) {
        plot_level_curve(level, 1000);
    }
}

void MainWindow::funcGraph(const points& ps, const QColor &color) {
    QVector<double> x, y;
    for (auto p : ps) {
        x.append(p.first);
        y.append(p.second);
    }
    ui->graphField->addGraph();
    ui->graphField->graph()->setData(x, y);
    ui->graphField->graph()->setPen(color);
}

void MainWindow::plot_stat(size_t dim) {
    std::vector<QColor> colors = {Qt::red,
                                  Qt::green,
                                  Qt::blue};
    std::vector<ufo::method_t> undim_methods = {ufo::golden_section_method,
                                                ufo::parabola_method,
                                                ufo::brents_method};
    for (size_t i = 0; i < 3; ++i) {
        points stat = gen_stat(METHODS[1], dim, undim_methods[i]);
        funcGraph(stat, colors[i]);
    }
}

double MainWindow::get_eps() const {
    bool ok = true;
    double val = ui->epsLineEdit->text().toDouble(&ok);
    if (!ok) {
        throw std::runtime_error("value is absent");
    }
    return val;
}

vector_t MainWindow::get_x0() const {
    bool ok = true;
    double x1 = ui->x1LineEdit->text().toDouble(&ok);
    double x2 = ui->x2LineEdit->text().toDouble(&ok);
    if (!ok) {
        throw std::runtime_error("value is absent");
    }
    return {x1, x2};
}


void MainWindow::start_method(size_t method_index) {
    try {
        double eps = get_eps();
        vector_t x0 = get_x0();
        data = METHODS[method_index](FUNCTION, x0, eps, UNDIM_METHOD);
        current_iteration = 0;
        current_method = method_index;
        show_iteration(false);
    } catch (std::runtime_error &) {
        // No operations.
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::show_iteration(bool first) {
    if (!first) {
        curve->data()->clear();
    }
    QVector<QCPCurveData> curveData;
//    QVector<double> x, y;
    for (size_t i = 0; i < current_iteration; ++i) {
        curveData.append(QCPCurveData(i, data[i][0], data[i][1]));
//        x.append(data[i][0]);
//        y.append(data[i][1]);
    }
    curve->setPen(QPen(Qt::red));
    curve->data()->set(curveData);
    ui->graphField->replot();
//    ui->graphField->addGraph();
//    ui->graphField->graph()->setData(x, y);
//    ui->graphField->graph()->setPen(QPen(Qt::red));
//    ui->graphField->replot();
}

void MainWindow::next() {
    if (current_iteration < data.size()) {
        ++current_iteration;
        show_iteration(false);
    }
}

void MainWindow::prev() {
    if (current_iteration > 0) {
        --current_iteration;
        show_iteration(false);
    }
}






