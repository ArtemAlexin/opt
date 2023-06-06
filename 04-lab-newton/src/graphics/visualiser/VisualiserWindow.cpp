#include <qcustomplot.h>
#include <VisualiserWindow.h>
#include <ui_VisualiserWindow.h>

VisualiserWindow::VisualiserWindow(QWidget *parent)
        : QMainWindow(parent),
          ui(new Ui::VisualiserWindow) {
    ui->setupUi(this);
    ui->graphField->setInteraction(QCP::iRangeZoom, true);
    this->setFixedSize(QSize(1385, 840));
    initMethods();
    initAxis();
    initPlot();
}

void VisualiserWindow::initMethods() {
    connect(ui->bfsButton, &QPushButton::released, this, [&]() { startMethod(0); });
    connect(ui->powellButton, &QPushButton::released, this, [&]() { startMethod(1); });
    connect(ui->classicNewtonButton, &QPushButton::released, this, [&]() { startMethod(2); });
    connect(ui->unidimSearchNewton, &QPushButton::released, this, [&]() { startMethod(3); });
    connect(ui->descentDirectionNewton, &QPushButton::released, this, [&]() { startMethod(4); });

    connect(ui->nextButton, &QPushButton::released, this, &VisualiserWindow::next);
    connect(ui->prevButton, &QPushButton::released, this, &VisualiserWindow::prev);
}

void VisualiserWindow::initAxis() const {
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

void VisualiserWindow::initPlot() {
    METHODS[0]({20, 20}, 0.001, f.function, f.gradient, f.gessian, data);
    methodPath = new QCPCurve(ui->graphField->xAxis, ui->graphField->yAxis);
    plotLevelCurves();
    showIteration();
    ui->levelLinesCheckBox->setCheckState(Qt::Checked);
    connect(ui->levelLinesCheckBox, &QCheckBox::stateChanged, this, [&](int state) {
        if (state) {
            for (auto *p : levelCurves) {
                p->data()->clear();
            }
            plotLevelCurves();
        } else {
            for (auto *p : levelCurves) {
                p->data()->clear();
            }
        }
        ui->graphField->replot();
    });
}

std::pair<double, double> solveQuadEquation(double A, double B, double C) {
    return {(-B - sqrt(B * B - 4 * A * C)) / (2 * A), (-B + sqrt(B * B - 4 * A * C)) / (2 * A)};
}

std::pair<double, double> calcInterval(const QuadFunction &f, double level) {
    double A = f.A.get(0, 1) * f.A.get(0, 1) - f.A.get(0, 0) * f.A.get(1, 1);
    double B = 2 * f.A.get(0, 1) * f.b[1] - 2 * f.A.get(1, 1) * f.b[0];
    double C = f.b[1] * f.b[1] - 2 * f.A.get(1, 1) * f.c + 2 * f.A.get(1, 1) * level;
    auto solution = solveQuadEquation(A, B, C);
    if (solution.first > solution.second) {
        std::swap(solution.first, solution.second);
    }
    double len = solution.second - solution.first;
    return {solution.first + len / 1000, solution.second - len / 1000};
}

Vector calcY(const QuadFunction &f, double x, double level) {
    double A = 0.5 * f.A.get(1, 1);
    double B = f.A.get(0, 1) * x + f.b[1];
    double C = 0.5 * f.A.get(0, 0) * x * x + f.b[0] * x + f.c - level;
    auto ys = solveQuadEquation(A, B, C);
    return {ys.first, ys.second};
}

void VisualiserWindow::plotLevelCurve(double level, int32_t n) {
    QVector<QCPCurveData> curveData;

    auto interval = calcInterval(f, level);
    double intervalLen = interval.second - interval.first;
    double h = intervalLen / n;

    double x = interval.first;
    for (int32_t i = 0; i < n; ++i) {
        double y = calcY(f, x, level)[0];
        if (y == y) {
            curveData.append(QCPCurveData(i, x, y));
        }
        x += h;
    }
    x -= h;
    for (int32_t i = 0; i < n; ++i) {
        double y = calcY(f, x, level)[1];
        if (y == y) {
            curveData.append(QCPCurveData(n + i, x, y));
        }
        x -= h;
    }
    curveData.append(QCPCurveData(2 * n, interval.first, calcY(f, interval.first, level)[0]));
    auto *curve = new QCPCurve(ui->graphField->xAxis, ui->graphField->yAxis);
    curve->setBrush(QBrush(QColor(0, 0, 255, 20)));
    curve->data()->set(curveData);
    levelCurves.push_back(curve);
}

void VisualiserWindow::plotLevelCurves() {
    for (auto *curve : levelCurves) {
        curve->data()->clear();
    }

    Vector x_min = data.back();
    double y_min = f.function(x_min);

    for (double level = y_min; level < y_min + 1000; level += 100) {
        plotLevelCurve(level, 1000);
    }
}

double VisualiserWindow::getEps() const {
    bool ok = true;
    double val = ui->epsLineEdit->text().toDouble(&ok);
    if (!ok) {
        throw std::runtime_error("value is absent");
    }
    return val;
}

Vector VisualiserWindow::getX0() const {
    bool ok = true;
    double x1 = ui->x1LineEdit->text().toDouble(&ok);
    double x2 = ui->x2LineEdit->text().toDouble(&ok);
    if (!ok) {
        throw std::runtime_error("value is absent");
    }
    return {x1, x2};
}


void VisualiserWindow::startMethod(size_t methodIndex) {
    try {
        double eps = getEps();
        Vector x0 = getX0();
        data.clear();
        METHODS[methodIndex](x0, eps, f.function, f.gradient, f.gessian, data);
        currentIteration = 1;
        currentMethod = methodIndex;
        showIteration();
    } catch (std::runtime_error &) {
        // No operations.
    }
}

VisualiserWindow::~VisualiserWindow() {
    delete ui;
}

void VisualiserWindow::showIteration() {
    QVector<QCPCurveData> curveData;
    for (size_t i = 0; i < currentIteration; ++i) {
        curveData.append(QCPCurveData(static_cast<double>(i), data[i][0], data[i][1]));
    }
    methodPath->setPen(QPen(Qt::red));
    methodPath->data()->set(curveData);
    ui->graphField->replot();
    ui->iterationLabel->setText(QString::number(currentIteration - 1));
}

void VisualiserWindow::next() {
    if (currentIteration < data.size()) {
        ++currentIteration;
        showIteration();
    }
}

void VisualiserWindow::prev() {
    if (currentIteration > 1) {
        --currentIteration;
        showIteration();
    }
}






