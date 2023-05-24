#ifndef ZORKUL_H_
#define ZORKUL_H_
#include "Character.h"
#include "Command.h"
#include "Parser.h"
#include "Room.h"

#include <QString>
#include <QTextBrowser>
#include <string>

class ZorkUL
{
private:
    void createRooms();
    void printHelp();
    string goRoom(Command command);
    string solvePuzzle(Puzzle puzzle, Command command);
    void printMessage(QTextBrowser *output, const QString &txt);

public:
    ZorkUL();
    Room *currentRoom;

    Parser parser;
    bool running;
    void play(QTextBrowser *output);
    bool processCommand(Command command, QTextBrowser *output);
    QString getInventory();
    Character *player;
};

#endif /*ZORKUL_H_*/
