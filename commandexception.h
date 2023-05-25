#ifndef COMMANDEXCEPTION_H
#define COMMANDEXCEPTION_H

#include <exception>
#include <string>

class CommandException : public std::exception
{
private:
    std::string errorMessage;

public:
    CommandException(const std::string &message);

    const char *what() const noexcept override;
};

#endif // COMMANDEXCEPTION_H
