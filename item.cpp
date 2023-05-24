#include "item.h"
#include <iostream>
using namespace std;

Item::Item(string inDescription) {
	description = inDescription;
}

string Item::getShortDescription()
{
	return description;
}
