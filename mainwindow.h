#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
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
    void on_mapButton_clicked();

private:
    Ui::MainWindow *ui;
    QTextBrowser *outputArea;
    QLineEdit *commandArea;
    QLabel *inventoryArea;
    QPushButton *mapButton;
    QPushButton *guiButton;

    ZorkUL game;

    void handleInput();
    void processInput(QString &inputText);
};
#endif // MAINWINDOW_H
