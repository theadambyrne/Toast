#include "commandexception.h"

CommandException::CommandException(const std::string &message)
    : errorMessage(message)
{}

const char *CommandException::what() const noexcept
{
    return errorMessage.c_str();
}
