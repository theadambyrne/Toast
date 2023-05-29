#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "GameObject.h"
#include "item.h"

#include <QString>
#include <string>
#include <vector>

using namespace std;

class Character : public GameObject
{
private:
    vector<Item> inventory;

public:
    Character(string description) { this->description = description; };
    string getShortDescription() const override;

    void addItem(Item item);
    void removeItem(Item item);
    bool hasItem(Item item);

    vector<Item> getInventory();
    QString getInventoryDescription();
};

#endif /*CHARACTER_H_*/
