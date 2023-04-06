#include "ZorkUL.h"
#include <iostream>

ZorkUL::ZorkUL()
{
    createRooms();
    inventory = {};
}

void ZorkUL::createRooms()
{
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i;

    a = new Room("a");
    a->addItem(new Item("x", 1, 11));
    a->addItem(new Item("y", 2, 22));
	b = new Room("b");
        b->addItem(new Item("xx", 3, 33));
        b->addItem(new Item("yy", 4, 44));
	c = new Room("c");
	d = new Room("d");
	e = new Room("e");
	f = new Room("f");
	g = new Room("g");
	h = new Room("h");
	i = new Room("i");

//             (N, E, S, W)
	a->setExits(f, b, d, c);
	b->setExits(NULL, NULL, NULL, a);
	c->setExits(NULL, a, NULL, NULL);
	d->setExits(a, e, NULL, i);
	e->setExits(NULL, NULL, NULL, d);
	f->setExits(NULL, g, a, h);
	g->setExits(NULL, NULL, NULL, f);
	h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL);

    currentRoom = a;
    running = false;
}

/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play(QTextBrowser *output)
{
    running = true;
    printWelcome(output);
}

void ZorkUL::printWelcome(QTextBrowser *output)
{
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
            printMessage(output, "go (direction), take (item), put (item), info, quit");

        else if (commandWord.compare("go") == 0)
            printMessage(output, QString::fromStdString(goRoom(command)));

        else if (commandWord.compare("take") == 0) {
            if (!command.hasSecondWord()) {
                printMessage(output, "incomplete input");
            } else if (command.hasSecondWord()) {
                int location = currentRoom->isItemInRoom(command.getSecondWord());

                if (location == 0) {
                    inventory.push_back(command.getSecondWord());

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

string ZorkUL::goRoom(Command command)
{
        if (!command.hasSecondWord()) {
            return "incomplete input";
        }

        string direction = command.getSecondWord();
        Room *nextRoom = currentRoom->nextRoom(direction);

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
        for (std::vector<std::string>::iterator t = inventory.begin(); t != inventory.end(); t++) {
            result.append(" " + *t);
        }
        return QString::fromStdString(result);
}
