#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "item.h"

#include <string>
#include <vector>

using namespace std;

class Character {
private:
    string description;

public:
    void addItem(Item item);
    void removeItem(Item item);

    Character(string description);

    string shortDescription();
    vector<Item> inventory;
};

#endif /*CHARACTER_H_*/
