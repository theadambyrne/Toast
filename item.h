#ifndef ITEM_H_
#define ITEM_H_

#include <string>
using namespace std;

class Item
{
private:
    string description;

public:
    Item(string description);
	string getShortDescription();
    bool operator==(const Item &other) const; // Add the equality comparison operator
};

#endif /*ITEM_H_*/
