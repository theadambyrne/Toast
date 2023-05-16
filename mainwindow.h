#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QTextBrowser>
#include "ZorkUL.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_goNorthButton_clicked();
    void on_mapButton_clicked();

    void on_goSouthButton_clicked();

    void on_goWestButton_clicked();

    void on_goEastButton_clicked();

    void on_startButton_clicked();
    void onTimerTimeout();

private:
    Ui::MainWindow *ui;
    QTextBrowser *outputArea;
    QLineEdit *commandArea;
    QLabel *inventoryArea;
    QPushButton *mapButton;
    QPushButton *guiButton;
    QFrame *itemsFrame;
    QPushButton *goNorthButton;
    QPushButton *goEastButton;
    QPushButton *goWestButton;
    QPushButton *goSouthButton;
    QPushButton *startButton;
    void startGame();
    ZorkUL game;
    QTimer *timer;
    int timeLimit;
    QProgressBar *progress;

    void handleInput();
    void processInput(QString &inputText);
};
#endif // MAINWINDOW_H
