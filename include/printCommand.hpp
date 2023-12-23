#pragma once
#include "command.hpp"

class PrintCommand : public Command
{
public:
    void interpret(std::istream& is, char& next, Parser& object);
};