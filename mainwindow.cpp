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

    inventoryArea = findChild<QLabel *>("inventoryLabel");
    mapButton = findChild<QPushButton *>("mapButton");
    guiButton = findChild<QPushButton *>("guiButton");

    inventoryArea->setVisible(false);
    mapButton->setVisible(false);
    guiButton->setVisible(false);

    // welcome message
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
        inventoryArea->setVisible(true);
        mapButton->setVisible(true);
        guiButton->setVisible(true);
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
        // dialog
        QDialog dialog(this);
        dialog.setWindowTitle("Map");

        // Create a grid layout to display the rooms
        QGridLayout *gridLayout = new QGridLayout(&dialog);

        // Create labels for each room and add them to the grid
        QLabel *roomA = new QLabel("[A]", &dialog);
        QLabel *roomB = new QLabel("[B]", &dialog);
        QLabel *roomC = new QLabel("[C]", &dialog);
        QLabel *roomD = new QLabel("[D]", &dialog);
        QLabel *roomE = new QLabel("[E]", &dialog);
        QLabel *roomF = new QLabel("[F]", &dialog);
        QLabel *roomG = new QLabel("[G]", &dialog);
        QLabel *roomH = new QLabel("[H]", &dialog);
        QLabel *roomI = new QLabel("[I]", &dialog);

        QLabel *path1 = new QLabel(" -- ", &dialog);
        QLabel *path2 = new QLabel(" -- ", &dialog);
        QLabel *path3 = new QLabel(" -- ", &dialog);
        QLabel *path4 = new QLabel("  |", &dialog);
        QLabel *path5 = new QLabel(" -- ", &dialog);
        QLabel *path6 = new QLabel(" -- ", &dialog);
        QLabel *path7 = new QLabel("  |", &dialog);
        QLabel *path8 = new QLabel(" -- ", &dialog);

        gridLayout->addWidget(roomH, 0, 1);
        gridLayout->addWidget(path1, 0, 2);
        gridLayout->addWidget(roomF, 0, 3);
        gridLayout->addWidget(path2, 0, 4);
        gridLayout->addWidget(roomG, 0, 5);

        gridLayout->addWidget(roomC, 2, 1);
        gridLayout->addWidget(path3, 2, 2);
        gridLayout->addWidget(path4, 1, 3);
        gridLayout->addWidget(roomA, 2, 3);
        gridLayout->addWidget(path5, 2, 4);
        gridLayout->addWidget(roomB, 2, 5);

        gridLayout->addWidget(roomI, 4, 1);
        gridLayout->addWidget(path6, 4, 2);
        gridLayout->addWidget(path7, 3, 3);
        gridLayout->addWidget(roomD, 4, 3);
        gridLayout->addWidget(path8, 4, 4);
        gridLayout->addWidget(roomE, 4, 5);

        // Set the dialog size to fit the content
        dialog.adjustSize();

        // Display the dialog
        dialog.exec();
    }
}
