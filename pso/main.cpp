#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(Driver::getInstance());
    w.show();

    return a.exec();
}
