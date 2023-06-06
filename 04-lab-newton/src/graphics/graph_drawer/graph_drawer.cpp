#include <GraphDrawerWindow.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphDrawerWindow w;
    w.show();
    return a.exec();
}
