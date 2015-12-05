#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // get driver
    Driver* driver = Driver::getInstance();

    // init ui
    QApplication a(argc, argv);
    MainWindow w(driver);

    // show ui
    w.show();

    // run app
    return a.exec();
}
