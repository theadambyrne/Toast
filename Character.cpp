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

string Character::longDescription()
{
    string ret = this->description;
    ret += "\n Item list:\n";
    for (vector<string>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
        ret += "\t" + (*i) + "\n";
    return ret;
}
