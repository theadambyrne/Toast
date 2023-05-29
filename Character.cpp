#include "Character.h"
#include <string>

void Character::addItem(Item item)
{
    inventory.push_back(item);
}

void Character::removeItem(Item item)
{
    auto it = std::find(inventory.begin(), inventory.end(), item);

    if (it != inventory.end()) {
        inventory.erase(it);
    }
}

bool Character::hasItem(Item item)
{
    auto it = std::find(inventory.begin(), inventory.end(), item);
    return it != inventory.end();
}

vector<Item> Character::getInventory()
{
    return inventory;
}

QString Character::getInventoryDescription()
{
    QString result = "Inventory:";
    for (Item &item : inventory) {
        result.append(" " + QString::fromStdString(item.getShortDescription()));
    }
    return result;
}

string Character::getShortDescription() const
{
    return description;
}
