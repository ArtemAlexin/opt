#pragma once

#include <QMainWindow>

#include <qcustomplot.h>
#include <unidim_methods.h>
#include <quasi_newton_methods.h>
#include <newton_methods.h>
#include <QuadFunction.h>
#include <logging.h>

QT_BEGIN_NAMESPACE
namespace Ui { class VisualiserWindow; }
QT_END_NAMESPACE

class VisualiserWindow : public QMainWindow {

    Q_OBJECT

public:
    VisualiserWindow(QWidget *parent = nullptr);
    ~VisualiserWindow();

    void setFunction(const QuadFunction& functionToExplore) {
        f = functionToExplore;
        plotLevelCurves();
        data.clear();
        METHODS[0]({20, 20}, 0.001, f.function, f.gradient, f.gessian, data);
    }

private:
    void initMethods();
    void initAxis() const;
    void initPlot();

    void plotLevelCurve(double level, int32_t n);
    void plotLevelCurves();

    using Points = std::vector<std::pair<double, double>>;

    double getEps() const;
    Vector getX0() const;
    void startMethod(size_t);

    void showIteration();
    void next();
    void prev();

    Ui::VisualiserWindow *ui;

    const std::vector<Logging::Method> METHODS = {
            QuasiNewtonMethods::bfsLogging,
            QuasiNewtonMethods::powellLogging,
            NewtonMethods::classicNewtonLog,
            NewtonMethods::unidimSearchNewtonLog,
            NewtonMethods::descentDirectionNewtonLog
    };

    QuadFunction f;

    Logging::EvalData data;
    size_t currentIteration = 1;
    size_t currentMethod = 0;

    QCPCurve *methodPath;
    std::vector<QCPCurve*> levelCurves;
};
