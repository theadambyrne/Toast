#include <QTimer>
#include <iostream>
#include <thread>

using namespace std;
#include "ZorkUL.h"

ZorkUL::ZorkUL()
{
    createRooms();
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
    printMessage(output, QString::fromStdString("\n" + currentRoom->longDescription()));
}

void ZorkUL::printMessage(QTextBrowser *output, const QString &txt)
{
    output->append("");
    for (const QChar &c : txt) {
        output->insertPlainText(c);
        output->moveCursor(QTextCursor::End);
    }
    output->append("");
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
            printMessage(output, "INFO TODO");
        //            printHelp();

        else if (commandWord.compare("map") == 0) {
            printMessage(output,
                         "[h] --- [f] --- [g]\n"
                         "         |         \n"
                         "         |         \n"
                         "[c] --- [a] --- [b]\n"
                         "         |         \n"
                         "         |         \n"
                         "[i] --- [d] --- [e]");
        }

        else if (commandWord.compare("go") == 0)
            printMessage(output, QString::fromStdString(goRoom(command)));

        else if (commandWord.compare("take") == 0) {
            if (!command.hasSecondWord()) {
                printMessage(output, "incomplete input");
            } else if (command.hasSecondWord()) {
                printMessage(output,
                             QString::fromStdString("you're trying to take "
                                                    + command.getSecondWord()));
                int location = currentRoom->isItemInRoom(command.getSecondWord());
                if (location < 0)
                    printMessage(output, QString::fromStdString("Item is not in room"));
                else
                    printMessage(output, QString::fromStdString("Item is in room"));

                printMessage(output, QString::fromStdString(&"Number "[location]));
                printMessage(output, QString::fromStdString(currentRoom->longDescription()));
            }
        }

        else if (commandWord.compare("put") == 0) {
        }
        /*
    {
    if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            itemsInRoom.push_Back;
        }
    }
*/
        else if (commandWord.compare("quit") == 0) {
            if (command.hasSecondWord())
                printMessage(output, QString::fromStdString("Overdefined Input"));
            else
                printMessage(output, "Quiting game");
            this->running = false;
            return true; /**signal to quit*/
        }
        return false;
}
/** COMMANDS **/
//void ZorkUL::printHelp() {
//        for (const auto &str : parser.showCommands()) {
//            printMessage(output, )
//        }
//}

string ZorkUL::goRoom(Command command)
{
        if (!command.hasSecondWord()) {
            return "incomplete input";
        }

        string direction = command.getSecondWord();

        // Try to leave current room.
        Room *nextRoom = currentRoom->nextRoom(direction);

        if (nextRoom == NULL)
            return "underdefined input";
        else {
            currentRoom = nextRoom;
            return currentRoom->longDescription();
        }
}

string ZorkUL::go(string direction)
{
    //Make the direction lowercase
    //transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
    //Move to the next room
    Room *nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return ("direction null");
    else {
        currentRoom = nextRoom;
        return currentRoom->longDescription();
    }
}
