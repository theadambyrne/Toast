#ifndef PARSER_H_
#define PARSER_H_

#include "Command.h"
#include "CommandWords.h"

#include <QLineEdit>

class Parser {
private:
	CommandWords *commands;

public:
    Parser();
    Command *getCommand(string txt);
    vector<string> showCommands();
};

#endif /*PARSER_H_*/
