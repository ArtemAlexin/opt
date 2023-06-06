#include <qcustomplot.h>
#include <GraphDrawerWindow.h>
#include <ui_GraphDrawerWindow.h>

GraphDrawerWindow::GraphDrawerWindow(QWidget *parent)
        : QMainWindow(parent),
          ui(new Ui::GraphDrawerWindow) {
    ui->setupUi(this);
    ui->graphField->setInteraction(QCP::iRangeZoom, true);
    this->setFixedSize(QSize(1385, 840));
}

void GraphDrawerWindow::drawGraph(const Points &ps, const QColor &color) {
    ui->graphField->graph()->data()->clear();
    QVector<double> x, y;
    for (auto p : ps) {
        x.append(p.first);
        y.append(p.second);
    }
    ui->graphField->addGraph();
    ui->graphField->graph()->setData(x, y);
    ui->graphField->graph()->setPen(color);
}

GraphDrawerWindow::~GraphDrawerWindow() {
    delete ui;
}
