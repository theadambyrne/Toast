#ifndef ROOM_H_
#define ROOM_H_

#include "item.h"
#include "puzzle.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

class Room
{
private:
    string description;
    string exitString();

    map<string, Room *> exits;
    vector <Item> itemsInRoom;


public:
    Room(string description);
    string shortDescription();
    string longDescription();

    int numberOfItems();
    vector<Item> items();
    void addItem(Item *inItem);
    string displayItem();
    int isItemInRoom(string inString);

    Room *nextRoom(string direction);
    void setExits(Room *north, Room *east, Room *south, Room *west);

    bool locked = false;
    string hint;
    Item *key;
    Puzzle *puzzle;
};

#endif
