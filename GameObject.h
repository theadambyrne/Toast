#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
using namespace std;

class GameObject
{
public:
    virtual string getShortDescription() const = 0;

protected:
    string description;
};

#endif // GAMEOBJECT_H
