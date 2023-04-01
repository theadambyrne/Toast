#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Toast");

    outputArea = findChild<QTextEdit *>("outputArea");
    commandArea = findChild<QLineEdit *>("commandArea");
    connect(commandArea, &QLineEdit::returnPressed, this, &MainWindow::handleInput);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleInput()
{
    QString inputText = commandArea->text();
    commandArea->clear();
    processInput(inputText);
}

void MainWindow::processInput(const QString &inputText)
{
    if (inputText == "start") {
        startGame();
    } else {
        // Handle other input commands...
    }
}

void MainWindow::startGame()
{
    outputArea->clear();
}
