#include "ZorkUL.h"
#include "Character.h"
#include "item.h"
#include "puzzle.h"
ZorkUL::ZorkUL()
{
    createRooms();
    player = new Character("player");
}

void ZorkUL::createRooms()
{
    Room *breadSlot, *crumbTray, *controlUnit, *timerUnit, *powerSupply;
    Item *wirecutters, *screwdriver;
    Puzzle *winCondition = new Puzzle("Which wire do you cut? try red, green or blue.", "red");

    breadSlot = new Room("Bread Slot");
    crumbTray = new Room("Crumb Tray");
    controlUnit = new Room("Control Unit");
    timerUnit = new Room("Timer");
    powerSupply = new Room("Power Supply");

    crumbTray->addItem(screwdriver = new Item("screwdriver"));
    controlUnit->addItem(wirecutters = new Item("wirecutters"));

    breadSlot->setExits(controlUnit, NULL, crumbTray, NULL);
    crumbTray->setExits(breadSlot, NULL, NULL, NULL);
    controlUnit->setExits(NULL, powerSupply, NULL, timerUnit);

    controlUnit->locked = true;
    controlUnit->key = screwdriver;
    controlUnit->hint = "Hmm lots of screws.";

    timerUnit->locked = true;
    timerUnit->key = wirecutters;
    timerUnit->hint = "You might need to cut some wires";
    timerUnit->puzzle = winCondition;

    powerSupply->locked = true;
    powerSupply->key = wirecutters;
    powerSupply->hint = "Probably some wires in there";
    powerSupply->puzzle = winCondition;

    currentRoom = breadSlot;
    running = false;
}

void ZorkUL::play(QTextBrowser *output)
{
    running = true;
    printMessage(output, QString::fromStdString(currentRoom->longDescription()));
}

void ZorkUL::printMessage(QTextBrowser *output, const QString &txt)
{
    output->append("");

    for (const QChar &c : txt) {
        output->insertPlainText(c);
        output->moveCursor(QTextCursor::End);
    }
    output->append("---");
}

bool ZorkUL::processCommand(Command command, QTextBrowser *output)
{
        if (command.isUnknown()) {
            printMessage(output, "Invalid input");
            return false;
        }

        string commandWord = command.getCommandWord();

        if (commandWord.compare("info") == 0)
            printMessage(output,
                         "go (direction), take (item), put (item), map, try (option), info, quit");

        else if (commandWord.compare("go") == 0) {
            printMessage(output, QString::fromStdString(goRoom(command)));
        }

        else if (commandWord.compare("try") == 0 && currentRoom->puzzle) {
            printMessage(output, QString::fromStdString(solvePuzzle(*currentRoom->puzzle, command)));
        }

        else if (commandWord.compare("map") == 0)
            output->insertHtml(
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

        else if (commandWord.compare("take") == 0) {
            if (!command.hasSecondWord()) {
                printMessage(output, "incomplete input");
            } else if (command.hasSecondWord()) {
                int location = currentRoom->isItemInRoom(command.getSecondWord());

                if (location == 0) {
                    player->addItem(command.getSecondWord());

                } else {
                    printMessage(output,
                                 QString::fromStdString(command.getSecondWord() + " is not in room "
                                                        + currentRoom->shortDescription()));
                }
            }
        }

        else if (commandWord.compare("put") == 0) {
            Item _item = Item(command.getSecondWord());

            if (player->hasItem(_item)) {
                player->removeItem(_item);
                printMessage(output,
                             QString::fromStdString(_item.getShortDescription() + " put in room"));
            } else {
                printMessage(output,
                             QString::fromStdString(_item.getShortDescription()
                                                    + " is not in room "));
            }
        }

        else if (commandWord.compare("quit") == 0) {
            if (command.hasSecondWord())
                printMessage(output, QString::fromStdString("overdefined input"));
            else
                printMessage(output, "Exited game");
            this->running = false;
            return true; /**signal to quit*/
        }

        return false;
}

string ZorkUL::solvePuzzle(Puzzle puzzle, Command command)
{
        if (!command.hasSecondWord()) {
            return "incomplete input";
        }

        string option = command.getSecondWord();

        if (puzzle.checkSolution(option)) {
            this->running = false;
            return "🏆 WINNER";
        }
        return "Uh oh wrong answer!";
}

string ZorkUL::goRoom(Command command)
{
        if (!command.hasSecondWord()) {
            return "incomplete input";
        }

        string direction = command.getSecondWord();
        Room *nextRoom = currentRoom->nextRoom(direction);
        if (currentRoom->nextRoom(direction) == NULL) {
            return "invalid direction";
        }

        if (nextRoom->locked) {
            if (player->hasItem(*nextRoom->key)) {
                currentRoom = nextRoom;
                return "Unlocked by " + nextRoom->key->getShortDescription() + "\n"
                       + currentRoom->longDescription();
            }
            return "Locked. " + nextRoom->hint;
        }

        currentRoom = nextRoom;
        return currentRoom->longDescription();
}
