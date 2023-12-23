#pragma once
#include "command.hpp"

class SetCommand : public Command
{
public:
    void interpret(std::istream& is, char& next, Parser& object);
};