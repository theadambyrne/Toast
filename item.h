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
};

#endif /*ITEM_H_*/
