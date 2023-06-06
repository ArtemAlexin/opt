#pragma once

#include <QMainWindow>

#include <qcustomplot.h>
#include <unidim_methods.h>
#include <quasi_newton_methods.h>
#include <QuadFunction.h>

QT_BEGIN_NAMESPACE
namespace Ui { class GraphDrawerWindow; }
QT_END_NAMESPACE

class GraphDrawerWindow : public QMainWindow {

    Q_OBJECT

public:
    GraphDrawerWindow(QWidget *parent = nullptr);
    ~GraphDrawerWindow();

    using Points = std::vector<std::pair<double, double>>;

    void drawGraph(const Points& ps, const QColor &color);

private:
    Ui::GraphDrawerWindow *ui;
};
