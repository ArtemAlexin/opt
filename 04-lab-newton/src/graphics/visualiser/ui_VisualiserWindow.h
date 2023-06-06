/********************************************************************************
** Form generated from reading UI file 'VisualiserWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISUALISERWINDOW_H
#define UI_VISUALISERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_VisualiserWindow
{
public:
    QWidget *centralwidget;
    QCustomPlot *graphField;
    QLineEdit *epsLineEdit;
    QPushButton *bfsButton;
    QPushButton *powellButton;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QLineEdit *x1LineEdit;
    QCheckBox *axiesCheckBox;
    QCheckBox *levelLinesCheckBox;
    QCheckBox *axiesLabelsCheckBox;
    QLineEdit *x2LineEdit;
    QPushButton *classicNewtonButton;
    QPushButton *unidimSearchNewton;
    QPushButton *descentDirectionNewton;
    QLabel *iterationLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *VisualiserWindow)
    {
        if (VisualiserWindow->objectName().isEmpty())
            VisualiserWindow->setObjectName(QString::fromUtf8("VisualiserWindow"));
        VisualiserWindow->resize(1392, 865);
        centralwidget = new QWidget(VisualiserWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphField = new QCustomPlot(centralwidget);
        graphField->setObjectName(QString::fromUtf8("graphField"));
        graphField->setGeometry(QRect(10, 10, 1201, 801));
        epsLineEdit = new QLineEdit(centralwidget);
        epsLineEdit->setObjectName(QString::fromUtf8("epsLineEdit"));
        epsLineEdit->setGeometry(QRect(1230, 10, 141, 29));
        bfsButton = new QPushButton(centralwidget);
        bfsButton->setObjectName(QString::fromUtf8("bfsButton"));
        bfsButton->setGeometry(QRect(1230, 130, 141, 71));
        powellButton = new QPushButton(centralwidget);
        powellButton->setObjectName(QString::fromUtf8("powellButton"));
        powellButton->setGeometry(QRect(1230, 210, 141, 71));
        nextButton = new QPushButton(centralwidget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setGeometry(QRect(1230, 690, 141, 51));
        prevButton = new QPushButton(centralwidget);
        prevButton->setObjectName(QString::fromUtf8("prevButton"));
        prevButton->setGeometry(QRect(1230, 760, 141, 51));
        x1LineEdit = new QLineEdit(centralwidget);
        x1LineEdit->setObjectName(QString::fromUtf8("x1LineEdit"));
        x1LineEdit->setGeometry(QRect(1230, 50, 141, 29));
        axiesCheckBox = new QCheckBox(centralwidget);
        axiesCheckBox->setObjectName(QString::fromUtf8("axiesCheckBox"));
        axiesCheckBox->setGeometry(QRect(1230, 550, 110, 27));
        axiesCheckBox->setAutoFillBackground(false);
        axiesCheckBox->setTristate(false);
        levelLinesCheckBox = new QCheckBox(centralwidget);
        levelLinesCheckBox->setObjectName(QString::fromUtf8("levelLinesCheckBox"));
        levelLinesCheckBox->setGeometry(QRect(1230, 610, 151, 27));
        levelLinesCheckBox->setTristate(false);
        axiesLabelsCheckBox = new QCheckBox(centralwidget);
        axiesLabelsCheckBox->setObjectName(QString::fromUtf8("axiesLabelsCheckBox"));
        axiesLabelsCheckBox->setGeometry(QRect(1230, 580, 141, 27));
        axiesLabelsCheckBox->setTristate(false);
        x2LineEdit = new QLineEdit(centralwidget);
        x2LineEdit->setObjectName(QString::fromUtf8("x2LineEdit"));
        x2LineEdit->setGeometry(QRect(1230, 90, 141, 29));
        classicNewtonButton = new QPushButton(centralwidget);
        classicNewtonButton->setObjectName(QString::fromUtf8("classicNewtonButton"));
        classicNewtonButton->setGeometry(QRect(1230, 290, 141, 71));
        unidimSearchNewton = new QPushButton(centralwidget);
        unidimSearchNewton->setObjectName(QString::fromUtf8("unidimSearchNewton"));
        unidimSearchNewton->setGeometry(QRect(1230, 370, 141, 71));
        descentDirectionNewton = new QPushButton(centralwidget);
        descentDirectionNewton->setObjectName(QString::fromUtf8("descentDirectionNewton"));
        descentDirectionNewton->setGeometry(QRect(1230, 450, 141, 91));
        iterationLabel = new QLabel(centralwidget);
        iterationLabel->setObjectName(QString::fromUtf8("iterationLabel"));
        iterationLabel->setGeometry(QRect(1230, 650, 141, 31));
        VisualiserWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(VisualiserWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1392, 26));
        VisualiserWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(VisualiserWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        VisualiserWindow->setStatusBar(statusbar);

        retranslateUi(VisualiserWindow);

        QMetaObject::connectSlotsByName(VisualiserWindow);
    } // setupUi

    void retranslateUi(QMainWindow *VisualiserWindow)
    {
        VisualiserWindow->setWindowTitle(QApplication::translate("VisualiserWindow", "VisualiserWindow", nullptr));
        epsLineEdit->setText(QString());
        epsLineEdit->setPlaceholderText(QApplication::translate("VisualiserWindow", "\316\265", nullptr));
        bfsButton->setText(QApplication::translate("VisualiserWindow", "\320\221\320\244\320\250-\320\274\320\265\321\202\320\276\320\264", nullptr));
        powellButton->setText(QApplication::translate("VisualiserWindow", "\320\234\320\265\321\202\320\276\320\264 \320\237\320\260\321\203\321\215\320\273\320\273\320\260", nullptr));
        nextButton->setText(QApplication::translate("VisualiserWindow", "\320\222\320\277\320\265\321\200\320\265\320\264", nullptr));
        prevButton->setText(QApplication::translate("VisualiserWindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        x1LineEdit->setText(QString());
        x1LineEdit->setPlaceholderText(QApplication::translate("VisualiserWindow", "x1", nullptr));
        axiesCheckBox->setText(QApplication::translate("VisualiserWindow", "\320\236\321\201\320\270", nullptr));
        levelLinesCheckBox->setText(QApplication::translate("VisualiserWindow", "\320\233\320\270\320\275\320\270\320\270 \321\203\321\200\320\276\320\262\320\275\321\217", nullptr));
        axiesLabelsCheckBox->setText(QApplication::translate("VisualiserWindow", "\320\237\320\276\320\264\320\277\320\270\321\201\320\270 \320\276\321\201\320\265\320\271", nullptr));
        x2LineEdit->setText(QString());
        x2LineEdit->setPlaceholderText(QApplication::translate("VisualiserWindow", "x2", nullptr));
        classicNewtonButton->setText(QApplication::translate("VisualiserWindow", "\320\232\320\273\320\260\321\201\321\201\320\270\321\207\320\265\321\201\320\272\320\270\320\271\n"
"\320\274\320\265\321\202\320\276\320\264\n"
"\320\235\321\214\321\216\321\202\320\276\320\275\320\260", nullptr));
        unidimSearchNewton->setText(QApplication::translate("VisualiserWindow", "\320\235\321\214\321\216\321\202\320\276\320\275 \321\201\n"
"\320\276\320\264\320\275\320\276\320\274\320\265\321\200\320\275\321\213\320\274\n"
"\320\277\320\276\320\270\321\201\320\272\320\276\320\274", nullptr));
        descentDirectionNewton->setText(QApplication::translate("VisualiserWindow", "\320\235\321\214\321\216\321\202\320\276\320\275 \321\201\n"
" \320\262\321\213\320\261\320\276\321\200\320\276\320\274\n"
"\320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217\n"
"\321\201\320\277\321\203\321\201\320\272\320\260", nullptr));
        iterationLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VisualiserWindow: public Ui_VisualiserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALISERWINDOW_H
