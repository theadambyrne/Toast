#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

template<typename T>
class GameObject
{
public:
    virtual T getShortDescription() const = 0;

protected:
    T description;
};

#endif // GAMEOBJECT_H
