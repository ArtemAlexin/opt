/********************************************************************************
** Form generated from reading UI file 'GraphDrawerWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHDRAWERWINDOW_H
#define UI_GRAPHDRAWERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_GraphDrawerWindow
{
public:
    QWidget *centralwidget;
    QCustomPlot *graphField;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GraphDrawerWindow)
    {
        if (GraphDrawerWindow->objectName().isEmpty())
            GraphDrawerWindow->setObjectName(QString::fromUtf8("GraphDrawerWindow"));
        GraphDrawerWindow->resize(1392, 865);
        centralwidget = new QWidget(GraphDrawerWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphField = new QCustomPlot(centralwidget);
        graphField->setObjectName(QString::fromUtf8("graphField"));
        graphField->setGeometry(QRect(10, 10, 1361, 801));
        GraphDrawerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GraphDrawerWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1392, 26));
        GraphDrawerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(GraphDrawerWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GraphDrawerWindow->setStatusBar(statusbar);

        retranslateUi(GraphDrawerWindow);

        QMetaObject::connectSlotsByName(GraphDrawerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GraphDrawerWindow)
    {
        GraphDrawerWindow->setWindowTitle(QApplication::translate("GraphDrawerWindow", "GraphDrawerWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphDrawerWindow: public Ui_GraphDrawerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHDRAWERWINDOW_H
