#include "mainwindow.h"
#include <QString>
#include <QTimer>
#include <QtWidgets>
#include "./ui_mainwindow.h"
#include "QtWidgets/qtextbrowser.h"
#include "Room.h"
#include "ZorkUL.h"
#include <algorithm>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
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
    timer = new QTimer(this);
    timeLimit = 60;
    progress = findChild<QProgressBar *>("progressBar");
    progress->setRange(0, timeLimit);
    progress->setValue(0);
    progress->setStyleSheet("QProgressBar::chunk {background-color: #ff4757;}");
    progress->setFormat("");
    itemsFrame->hide();
    roomItemsFrame->hide();
    itemsFrameLabel->hide();
    roomItemsFrameLabel->hide();

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
    updateInventoryFrame();
    updateRoomItems();
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
        itemsFrame->show();
        roomItemsFrame->show();
        itemsFrameLabel->show();
        roomItemsFrameLabel->show();
        startButton->hide();
        timer->start(1000);

    } else if (game.running) {
        Command *command = game.parser.getCommand(inputText.toStdString());
        game.processCommand(*command, outputArea);
        inventoryArea->setText(game.getInventory());

        updateRoomItems();
        updateInventoryFrame();

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
        QPushButton *btn = new QPushButton(QString::fromStdString(item.getShortDescription()));
        btn->setParent(roomItemsFrame);
        roomItemsFrame->show();

        connect(btn, &QPushButton::clicked, [btn, item, this]() {
            this->game.player->addItem(((Item) item).getShortDescription());
            this->updateRoomItems();
            updateInventoryFrame();
            inventoryArea->setText(game.getInventory());
            btn->deleteLater();
        });
    }
}

inline void MainWindow::updateInventoryFrame()
{
    for (const std::string &str : game.player->itemsInCharacter) {
        QPushButton *btn = new QPushButton(QString::fromStdString(str));
        btn->setParent(itemsFrame);
        itemsFrame->show();
        connect(btn, &QPushButton::clicked, [btn, this, str]() {
            game.player->itemsInCharacter.erase(std::remove(game.player->itemsInCharacter.begin(),
                                                            game.player->itemsInCharacter.end(),
                                                            str),
                                                game.player->itemsInCharacter.end());
            inventoryArea->setText(game.getInventory());
            updateRoomItems();
            updateInventoryFrame();
            btn->deleteLater();
        });
    }
}

void MainWindow::on_goNorthButton_clicked()
{
    game.processCommand(*game.parser.getCommand("go north"), outputArea);
    updateRoomItems();
    updateInventoryFrame();
}

void MainWindow::on_goSouthButton_clicked()
{
    game.processCommand(*game.parser.getCommand("go south"), outputArea);
    updateRoomItems();
    updateInventoryFrame();
}

void MainWindow::on_goWestButton_clicked()
{
    game.processCommand(*game.parser.getCommand("go west"), outputArea);
    updateRoomItems();
    updateInventoryFrame();
}

void MainWindow::on_goEastButton_clicked()
{
    game.processCommand(*game.parser.getCommand("go east"), outputArea);
    updateInventoryFrame();
    updateRoomItems();
}

void MainWindow::on_startButton_clicked()
{
    if (!this->game.running)
    {
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
        updateRoomItems();
    }
}
