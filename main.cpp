#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1200, 700);
    QApplication::setWindowIcon(QIcon(":icons/toast.png"));
    w.show();

    return a.exec();
}
