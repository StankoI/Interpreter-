#pragma once
#include "command.hpp"

class FuncCommand : public Command
{
public:
    void interpret(std::istream& is, char& next, Parser& object);
};