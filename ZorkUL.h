#ifndef ZORKUL_H_
#define ZORKUL_H_
#include "Command.h"
#include "Parser.h"
#include "Room.h"

#include <QString>
#include <QTextBrowser>
#include <string>

class ZorkUL {
private:
	Room *currentRoom;
	void createRooms();
    void printHelp();
    string goRoom(Command command);
    void createItems();
    void displayItems();
    void printWelcome(QTextBrowser *output);
    void printMessage(QTextBrowser *output, const QString &txt);

public:
    ZorkUL();
    Parser parser;
    bool running;
    void play(QTextBrowser *output);
    bool processCommand(Command command, QTextBrowser *output);
};

#endif /*ZORKUL_H_*/
