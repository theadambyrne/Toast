#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QTextEdit>
#include <qtextbrowser.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTextBrowser *outputArea;
    QLineEdit *commandArea;

    void handleInput();
    void startGame();
    void processInput(const QString &inputText);
    void typeText(const QString &txt, QTextBrowser *output);
};
#endif // MAINWINDOW_H
