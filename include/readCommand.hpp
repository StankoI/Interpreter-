#pragma once
#include "command.hpp"

class ReadCommand : public Command
{
public:
    void interpret(std::istream& is, char& next, Parser& object);
};