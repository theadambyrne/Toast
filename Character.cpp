#include "Character.h"
#include <string>

Character::Character(string description)
{
    this->description = description;
}

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
