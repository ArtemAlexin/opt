#include <VisualiserWindow.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VisualiserWindow w;
    w.show();
    w.setFunction(f1);
    return a.exec();
}
