#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QtWidgets/qtextbrowser.h"
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Toast");

    outputArea = findChild<QTextBrowser *>("outputArea");
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
        typeText(inputText, outputArea);
    }
}

void MainWindow::startGame()
{
    typeText("Hello and welcome!", outputArea);
}

void MainWindow::typeText(const QString &txt, QTextBrowser *output)
{
    output->clear();

    for (const QChar &character : txt) {
        output->insertPlainText(character);
    }
}
