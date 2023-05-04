#include "mainwindow.h"
#include <QString>
#include <QTimer>
#include <QtWidgets>
#include "./ui_mainwindow.h"
#include "QtWidgets/qtextbrowser.h"
#include "ZorkUL.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Toast");

    outputArea = findChild<QTextBrowser *>("outputArea");
    outputArea->setReadOnly(true);
    outputArea->setTextInteractionFlags(Qt::NoTextInteraction);
    outputArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    outputArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    commandArea = findChild<QLineEdit *>("commandArea");
    commandArea->setPlaceholderText("Enter commands here ...");
    commandArea->setFocus();

    outputArea->setHtml(
        "<center>"
        "<h1>Toast!</h1>"
        "<p>A Zork inspired text-adventure game with GUI controls.</p></center><hr/><br/>"
        "<p>While making your toast this morning, you have been shrunk down and trapped inside the "
        "toaster.<br/>Escape before your toast pops or you're toast!<br/>"
        "<i>by Adam Byrne</i>"
        "<br/><br/><h4>Type <u>start</u> to embark on your adventure.</h4>"
        "</p>");

    connect(commandArea, &QLineEdit::returnPressed, this, &MainWindow::handleInput);

    ZorkUL game;

    inventoryArea = findChild<QLabel *>("inventoryLabel");
    mapButton = findChild<QPushButton *>("mapButton");
    goNorthButton = findChild<QPushButton *>("goNorthButton");
    goEastButton = findChild<QPushButton *>("goEastButton");
    goWestButton = findChild<QPushButton *>("goWestButton");
    goSouthButton = findChild<QPushButton *>("goSouthButton");
    startButton = findChild<QPushButton *>("startButton");

    inventoryArea->hide();
    mapButton->hide();
    goNorthButton->hide();
    goEastButton->hide();
    goWestButton->hide();
    goSouthButton->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleInput()
{
    QString inputText = commandArea->text();
    if (inputText != "") {
        processInput(inputText);
        commandArea->clear();
        commandArea->setFocus();
    }
}

void MainWindow::processInput(QString &inputText)
{
    if (inputText == "start" && !game.running) {
        outputArea->clear();
        game.play(outputArea);
        inventoryArea->show();
        mapButton->show();
        goNorthButton->show();
        goEastButton->show();
        goWestButton->show();
        goSouthButton->show();
    } else if (game.running) {
        Command *command = game.parser.getCommand(inputText.toStdString());
        game.processCommand(*command, outputArea);
        inventoryArea->setText(game.getInventory());
        delete command;
    }
}

void MainWindow::on_mapButton_clicked()
{
    if (game.running) {
        this->outputArea->insertHtml(
            "<br/>"
            "<table border=1 style='border-collapse: collapse; border-color:black;'>"
            "<tr>"
            "<td style='padding:10px; text-align:center;'>&#x1f512; Timer</td>"
            "<td style='padding:10px; text-align:center;'>&#x1f512; Control Unit</td>"
            "<td style='padding:10px; text-align:center;'>&#x1f512; Power Supply</td>"
            "</tr>"
            "<tr>"
            "<td style='background-color:black;'>&nbsp;</td>"
            "<td style='padding:10px; text-align:center;'>Bread Slot</td>"
            "<td style='background-color:black;'>&nbsp;</td>"
            "</tr>"
            "<tr>"
            "<td style='background-color:black;'>&nbsp;</td>"
            "<td style='padding:10px; text-align:center;'>Crumb Tray</td>"
            "<td style='background-color:black;'>&nbsp;</td>"
            "</tr>"
            "</table>"
            "<br/>");
    }
}

void MainWindow::on_goNorthButton_clicked()
{
    game.processCommand(*game.parser.getCommand("go north"), outputArea);
}

void MainWindow::on_goSouthButton_clicked()
{
    game.processCommand(*game.parser.getCommand("go south"), outputArea);
}

void MainWindow::on_goWestButton_clicked()
{
    game.processCommand(*game.parser.getCommand("go west"), outputArea);
}

void MainWindow::on_goEastButton_clicked()
{
    game.processCommand(*game.parser.getCommand("go east"), outputArea);
}

void MainWindow::on_startButton_clicked()
{
    if (!this->game.running) {
        this->game.running = true;
        this->outputArea->clear();
        this->game.play(outputArea);
        this->inventoryArea->show();
        this->mapButton->show();
        this->goNorthButton->show();
        this->goEastButton->show();
        this->goWestButton->show();
        this->goSouthButton->show();
        this->startButton->hide();
    }
}
