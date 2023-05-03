#include "ZorkUL.h"
#include "Character.h"
#include "puzzle.h"
#include <iostream>

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

/**
 *  Main play routine.  Loops until end of play.
 */
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

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
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
            // remove from inventory
            auto it = std::find(inventory.begin(), inventory.end(), command.getSecondWord());
            if (it != inventory.end()) {
                inventory.erase(std::remove(inventory.begin(),
                                            inventory.end(),
                                            command.getSecondWord()),
                                inventory.end());
                printMessage(output,
                             QString::number(currentRoom->isItemInRoom(command.getSecondWord())));
            } else {
                printMessage(output,
                             QString::fromStdString(command.getSecondWord()
                                                    + " not found in inventory"));
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

bool ZorkUL::hasKey(Item *key, Character *player)
{
        for (std::vector<std::string>::iterator t = player->itemsInCharacter.begin();
             t != player->itemsInCharacter.end();
             t++) {
            if (key->getShortDescription() == *t)
                return true;
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
            return "🏆 WIN";
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
        if (nextRoom->locked) {
            if (hasKey(nextRoom->key, player)) {
                currentRoom = nextRoom;
                return "Unlocked by " + nextRoom->key->getShortDescription() + "\n"
                       + currentRoom->longDescription();

            } else {
                return "Locked. " + nextRoom->hint;
            }
        }
        if (nextRoom != NULL) {
            currentRoom = nextRoom;
            return currentRoom->longDescription();
        } else {
            return "invalid direction";
        }
}

QString ZorkUL::getInventory()
{
        string result = "Inventory:";
        for (std::vector<std::string>::iterator t = player->itemsInCharacter.begin();
             t != player->itemsInCharacter.end();
             t++) {
            result.append(" " + *t);
        }
        return QString::fromStdString(result);
}
