#ifndef ZORKUL_H_
#define ZORKUL_H_
#include "Character.h"
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
    vector<string> inventory;

public:
    ZorkUL();
    Parser parser;
    bool running;
    void play(QTextBrowser *output);
    bool processCommand(Command command, QTextBrowser *output);
    QString getInventory();
    Character *player;
};

#endif /*ZORKUL_H_*/
