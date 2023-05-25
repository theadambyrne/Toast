#include "mainwindow.h"
#include <QTimer>
#include <QtWidgets>
#include "./ui_mainwindow.h"
#include "QtWidgets/qtextbrowser.h"
#include "Room.h"
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

    itemsFrame = findChild<QFrame *>("itemsFrame"); // inventory
    roomItemsFrame = findChild<QFrame *>("roomItemsFrame");
    itemsFrameLabel = findChild<QLabel *>("inventoryFrameLabel");
    roomItemsFrameLabel = findChild<QLabel *>("roomItemsFrameLabel");
    timerText = findChild<QLabel *>("timerText");

    outputArea->setHtml(
        "<center>"
        "<h1>Toast!</h1>"
        "<p>A Zork inspired text-adventure game with GUI controls.</p></center><hr/><br/>"
        "<p>While making your toast this morning, you have been shrunk down and trapped inside the "
        "toaster.<br/>Escape before your toast pops or you're toast!<br/>"
        "<i>by Adam Byrne</i>"
        "<br/><br/><h4>Type <u>start</u> to embark on your adventure.</h4>"
        "</p>");


    ZorkUL game;
    timer = new QTimer(this);

    inventoryArea = findChild<QLabel *>("inventoryLabel");
    mapButton = findChild<QPushButton *>("mapButton");
    goNorthButton = findChild<QPushButton *>("goNorthButton");
    goEastButton = findChild<QPushButton *>("goEastButton");
    goWestButton = findChild<QPushButton *>("goWestButton");
    goSouthButton = findChild<QPushButton *>("goSouthButton");
    startButton = findChild<QPushButton *>("startButton");
    progress = findChild<QProgressBar *>("progressBar");

    inventoryArea->hide();
    mapButton->hide();
    goNorthButton->hide();
    goEastButton->hide();
    goWestButton->hide();
    goSouthButton->hide();
    timeLimit = 60;
    progress->setRange(0, timeLimit);
    progress->setValue(0);
    progress->setStyleSheet("QProgressBar::chunk {background-color: #ff4757;}");
    progress->setFormat("");
    itemsFrame->hide();
    roomItemsFrame->hide();
    itemsFrameLabel->hide();
    roomItemsFrameLabel->hide();

    connect(commandArea, &QLineEdit::returnPressed, this, &MainWindow::handleInput);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleInput()
{
    QString inputText = commandArea->text();
    if (inputText != "")
    {
        processInput(inputText);
        commandArea->clear();
        commandArea->setFocus();
    }
}

void MainWindow::onTimerTimeout()
{
    if (progress->value() > 59 && game.running)
    {
        outputArea->clear();
        outputArea->insertPlainText("Game Over");
        game.running = false;
    }
    else if (game.running)
    {
        progress->setValue(progress->value() + 1);
        timerText->setText(
            QString::fromStdString(std::to_string(timeLimit - progress->value()) + "s left"));
    }
    //    else {
    //        outputArea->clear();
    //        outputArea->insertPlainText("WINNER");
    //        outputArea->insertPlainText(" ");
    //        outputArea->insertPlainText(
    //            QString::fromStdString(std::to_string(timeLimit - progress->value())));
    //        game.running = false;
    //    }
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
        itemsFrame->show();
        roomItemsFrame->show();
        itemsFrameLabel->show();
        roomItemsFrameLabel->show();
        startButton->hide();
        timer->start(1000);

    } else if (game.running) {
        Command *command = game.parser.getCommand(inputText.toStdString());
        game.processCommand(*command, outputArea);
        inventoryArea->setText(game.player->getInventoryDescription());
        updateInventoryFrame();
        updateRoomItems();
        delete command;
    }
}

void MainWindow::on_mapButton_clicked()
{
    if (game.running)
    {
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

inline void MainWindow::updateRoomItems()
{
    for (Item &item : game.currentRoom->items()) {
        if (!game.player->hasItem(item)) {
            std::string name = item.getShortDescription();

            QPushButton *btn = new QPushButton(QString::fromStdString(name));
            btn->setParent(roomItemsFrame);
            btn->show();

            connect(btn, &QPushButton::clicked, [name, this, btn]() {
                QString cmd = QString::fromStdString("take " + name);
                processInput(cmd);
                btn->deleteLater();
            });
        }
    }
    roomItemsFrame->show();
}

inline void MainWindow::updateInventoryFrame()
{
    QObjectList kids = itemsFrame->children();
    for (Item &item : game.player->getInventory()) {
        std::string name = item.getShortDescription();
        QPushButton *btn = new QPushButton(QString::fromStdString(name));
        if (!kids.contains(btn)) {
            btn->setParent(itemsFrame);
            btn->show();

            connect(btn, &QPushButton::clicked, [name, this, btn]() {
                QString cmd = QString::fromStdString("put " + name);
                processInput(cmd);
                btn->deleteLater();
            });
        }
    }
    itemsFrame->show();
}

void MainWindow::on_goNorthButton_clicked()
{
    QString cmd = "go north";
    processInput(cmd);
}

void MainWindow::on_goSouthButton_clicked()
{
    QString cmd = "go south";
    processInput(cmd);
}

void MainWindow::on_goWestButton_clicked()
{
    QString cmd = "go west";
    processInput(cmd);
}

void MainWindow::on_goEastButton_clicked()
{
    QString cmd = "go east";
    processInput(cmd);
}

void MainWindow::on_startButton_clicked()
{
    if (!game.running) {
        game.running = true;
        timer->start(1000);

        outputArea->clear();
        game.play(outputArea);

        inventoryArea->show();
        mapButton->show();
        goNorthButton->show();
        goEastButton->show();
        goWestButton->show();
        goSouthButton->show();
        itemsFrame->show();
        roomItemsFrame->show();
        itemsFrameLabel->show();
        roomItemsFrameLabel->show();
        startButton->hide();
    }
}
