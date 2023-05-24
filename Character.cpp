#include "Character.h"
#include <string>

Character::Character(string description)
{
    this->description = description;
}
void Character::addItem(string item)
{
    itemsInCharacter.push_back(item);
}
