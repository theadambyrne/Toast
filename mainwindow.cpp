#include "mainwindow.h"
#include "./ui_mainwindow.h"

extern QString name = QString();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Toast");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->setWindowTitle(name + " - Toast!");
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    name = arg1;
    this->setWindowTitle(name + " - Toast");
}
