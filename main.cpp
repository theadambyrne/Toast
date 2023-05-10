#include <QLocale>
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1150, 700);

    // enforce window size
    w.setMaximumHeight(700);
    w.setMinimumHeight(700);

    w.setMinimumWidth(1150);
    w.setMaximumWidth(1150);

    //    QApplication::setWindowIcon(QIcon(":icons/toast.png"));
    w.show();

    return a.exec();
}
