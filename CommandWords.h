#ifndef COMMANDWORDS_H_
#define COMMANDWORDS_H_

#include <string>
#include <vector>
using namespace std;

class CommandWords {
private:
	static vector<string> validCommands;

public:
	CommandWords();
	bool isCommand(string aString);
    vector<string> showAll();
};


#endif /*COMMANDWORDS_H_*/
