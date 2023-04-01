#include "mainwindow.h"
#include <QTimer>
#include "./ui_mainwindow.h"
#include "QtWidgets/qtextbrowser.h"

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
    outputArea->clear();
    typeText("Hello and welcome!", outputArea);
}

void MainWindow::typeText(const QString &txt, QTextBrowser *output)
{
    QTimer *timer = new QTimer(this);
    int currentIndex = 0;

    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (currentIndex < txt.size()) {
            output->insertPlainText(txt[currentIndex]);
            currentIndex++;
            timer->start(50); // delay in milliseconds
        } else {
            timer->deleteLater();
        }
    });

    timer->start(50); // start the timer
}
