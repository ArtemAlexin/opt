#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "methods/grad_methods.h"
#include "undim_methods/undim_methods.h"
#include "qcustomplot/qcustomplot.h"

namespace grad = grad_methods;
namespace ufo = undim_methods;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init_eps_x();
    void init_methods();
    void init_axis() const;
    void init_plot();

    void plot_level_curve(double level, int32_t n);
    void plot_level_curves();

    using points = std::vector<std::pair<double, double>>;

    void funcGraph(const points& ps, const QColor &color);
    void plot_stat(size_t dim);

    double get_eps() const;
    vector_t get_x0() const;
    void start_method(size_t);

    void show_iteration(bool);
    void next();
    void prev();

    Ui::MainWindow *ui;

    inline static const std::vector<grad::method> METHODS = {grad::grad_descent, grad::quick_grad_descent, grad::conjugate_grad};
    QCPCurve *curve;
    std::vector<QCPCurve*> levelCurves;
    grad::eval_data data;
    size_t current_iteration;
    size_t current_method = 0;
};
#endif // MAINWINDOW_H
