#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
#include <vector>

using namespace std;

class Character {
private:
    string description;

public:
    void addItem(string Item);
    Character(string description);
    string shortDescription();
    vector<string> itemsInCharacter;
};

#endif /*CHARACTER_H_*/
