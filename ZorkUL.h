#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"

#include <QLineEdit>
#include <QString>
#include <QTextBrowser>
#include <iostream>
#include <string>
using namespace std;

class ZorkUL {
private:
	Room *currentRoom;
	void createRooms();
    void printHelp();
    string goRoom(Command command);
    void createItems();
    void displayItems();

public:
    Parser parser;
    bool processCommand(Command command, QTextBrowser *output);
    bool running;
    ZorkUL();
    void play(QTextBrowser *output);
    string go(string direction);
    void printWelcome(QTextBrowser *output);
    void printMessage(QTextBrowser *output, const QString &txt);
};

#endif /*ZORKUL_H_*/
