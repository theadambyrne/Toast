#ifndef ROOM_H_
#define ROOM_H_

#include "item.h"
#include "puzzle.h"
#include <map>
#include <string>
#include <vector>
using namespace std;
using std::vector;

class Room {

private:
	string description;
	map<string, Room*> exits;
	string exitString();
    vector <Item> itemsInRoom;


public:
    int numberOfItems();
    vector<Item> items();
    Room(string description);
    void setExits(Room *north, Room *east, Room *south, Room *west);
	string shortDescription();
	string longDescription();
	Room* nextRoom(string direction);
    void addItem(Item *inItem);
    string displayItem();
    int isItemInRoom(string inString);
    bool locked = false;
    string hint;
    Item *key;
    Puzzle *puzzle;
};

#endif
