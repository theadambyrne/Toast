#ifndef ITEM_H_
#define ITEM_H_

#include "GameObject.h"

#include <string>
using namespace std;

class Item : public GameObject
{
public:
    Item(string description) { this->description = description; };
    bool operator==(const Item &other) const; // Add the equality comparison operator
    string getShortDescription() const override;
};

#endif /*ITEM_H_*/
