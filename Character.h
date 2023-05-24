#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "item.h"

#include <QString>
#include <string>
#include <vector>

using namespace std;

class Character {
private:
    string description;
    vector<Item> inventory;

public:
    void addItem(Item item);
    void removeItem(Item item);

    Character(string description);

    string shortDescription();
    bool hasItem(Item item);
    vector<Item> getInventory();
    QString getInventoryDescription();
};

#endif /*CHARACTER_H_*/
