/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QCustomPlot *graphField;
    QLineEdit *epsLineEdit;
    QPushButton *gradButtom;
    QPushButton *quickGradButton;
    QPushButton *conjGradButton;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QLineEdit *x1LineEdit;
    QCheckBox *axiesCheckBox;
    QCheckBox *levelLinesCheckBox;
    QCheckBox *axiesLabelsCheckBox;
    QLineEdit *x2LineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1392, 865);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphField = new QCustomPlot(centralwidget);
        graphField->setObjectName(QString::fromUtf8("graphField"));
        graphField->setGeometry(QRect(10, 10, 1201, 801));
        epsLineEdit = new QLineEdit(centralwidget);
        epsLineEdit->setObjectName(QString::fromUtf8("epsLineEdit"));
        epsLineEdit->setGeometry(QRect(1230, 10, 141, 29));
        gradButtom = new QPushButton(centralwidget);
        gradButtom->setObjectName(QString::fromUtf8("gradButtom"));
        gradButtom->setGeometry(QRect(1230, 130, 141, 71));
        quickGradButton = new QPushButton(centralwidget);
        quickGradButton->setObjectName(QString::fromUtf8("quickGradButton"));
        quickGradButton->setGeometry(QRect(1230, 210, 141, 71));
        conjGradButton = new QPushButton(centralwidget);
        conjGradButton->setObjectName(QString::fromUtf8("conjGradButton"));
        conjGradButton->setGeometry(QRect(1230, 290, 141, 71));
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
        axiesCheckBox->setGeometry(QRect(1230, 570, 110, 27));
        axiesCheckBox->setAutoFillBackground(false);
        axiesCheckBox->setTristate(false);
        levelLinesCheckBox = new QCheckBox(centralwidget);
        levelLinesCheckBox->setObjectName(QString::fromUtf8("levelLinesCheckBox"));
        levelLinesCheckBox->setGeometry(QRect(1230, 630, 151, 27));
        levelLinesCheckBox->setTristate(false);
        axiesLabelsCheckBox = new QCheckBox(centralwidget);
        axiesLabelsCheckBox->setObjectName(QString::fromUtf8("axiesLabelsCheckBox"));
        axiesLabelsCheckBox->setGeometry(QRect(1230, 600, 141, 27));
        axiesLabelsCheckBox->setTristate(false);
        x2LineEdit = new QLineEdit(centralwidget);
        x2LineEdit->setObjectName(QString::fromUtf8("x2LineEdit"));
        x2LineEdit->setGeometry(QRect(1230, 90, 141, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1392, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        epsLineEdit->setText(QString());
        epsLineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\316\265", nullptr));
        gradButtom->setText(QApplication::translate("MainWindow", "\320\234\320\265\321\202\320\276\320\264\n"
"\320\263\321\200\320\260\320\264\320\270\320\265\320\275\321\202\320\275\320\276\320\263\320\276\n"
"\321\201\320\277\321\203\321\201\320\272\320\260", nullptr));
        quickGradButton->setText(QApplication::translate("MainWindow", "\320\234\320\265\321\202\320\276\320\264\n"
"\320\275\320\260\320\270\321\201\320\272\320\276\321\200\320\265\320\271\321\210\320\265\320\263\320\276\n"
"\321\201\320\277\321\203\321\201\320\272\320\260", nullptr));
        conjGradButton->setText(QApplication::translate("MainWindow", "\320\234\320\265\321\202\320\276\320\264\n"
"\321\201\320\276\320\277\321\200\321\217\320\266\320\265\320\275\320\275\321\213\321\205\n"
"\320\263\321\200\320\260\320\264\320\270\320\265\320\275\321\202\320\276\320\262", nullptr));
        nextButton->setText(QApplication::translate("MainWindow", "\320\222\320\277\320\265\321\200\320\265\320\264", nullptr));
        prevButton->setText(QApplication::translate("MainWindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        x1LineEdit->setText(QString());
        x1LineEdit->setPlaceholderText(QApplication::translate("MainWindow", "x1", nullptr));
        axiesCheckBox->setText(QApplication::translate("MainWindow", "\320\236\321\201\320\270", nullptr));
        levelLinesCheckBox->setText(QApplication::translate("MainWindow", "\320\233\320\270\320\275\320\270\320\270 \321\203\321\200\320\276\320\262\320\275\321\217", nullptr));
        axiesLabelsCheckBox->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\277\320\270\321\201\320\270 \320\276\321\201\320\265\320\271", nullptr));
        x2LineEdit->setText(QString());
        x2LineEdit->setPlaceholderText(QApplication::translate("MainWindow", "x2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
