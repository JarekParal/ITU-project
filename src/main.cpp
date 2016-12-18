#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("ITU-project Paint");
    w.resize(1024,600);
    w.show();

    return a.exec();
}
