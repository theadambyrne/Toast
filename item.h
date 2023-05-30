#ifndef ITEM_H_
#define ITEM_H_

#include "GameObject.h"

#include <string>
using namespace std;

class Item : public GameObject<string>
{
public:
    Item(string description) { this->description = description; };
    bool operator==(const Item &other) const;
    string getShortDescription() const override;
};

#endif /*ITEM_H_*/
