#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ufo/unidimensional_function_optimization.h"

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace ufo = unidimensional_function_optimization;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ufo::to_eval sample, QWidget *parent = nullptr);
    ~MainWindow();

private:
    void funcGraph(const ufo::func_t &f, const ufo::segment &seg, const QColor &color = Qt::blue);
    void point(double x, double y, const QColor &color = Qt::red);
    void clearAllExceptGraph();
    void iteration();
    void parabola_iteration();

    void connectMethodButtons();
    void setMethodAndShow(size_t num);

    void showPrevIteration();
    void showNextIteration();

    Ui::MainWindow *ui;

    ufo::func_t sample_f;
    ufo::segment sample_seg;
    std::array<ufo::eval_data, 5> data;
    size_t method_num = 0;
    size_t it_num = 0;

    std::array<QPushButton *,5> buttons;
};
#endif // MAINWINDOW_H
