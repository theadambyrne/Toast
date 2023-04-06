#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1200, 700);

    // enforce window size
    w.setMaximumHeight(700);
    w.setMinimumHeight(700);
    w.setMaximumWidth(1200);
    w.setMinimumWidth(1200);

    QApplication::setWindowIcon(QIcon(":icons/toast.png"));
    w.show();

    return a.exec();
}
