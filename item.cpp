#include "item.h"

using namespace std;

string Item::getShortDescription() const
{
    return description;
}

bool Item::operator==(const Item &other) const
{
    return description == other.description;
}
