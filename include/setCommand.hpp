#pragma once
#include "command.hpp"
/// клас SetCommand, наследник на Command който override-ва функцията interpret, като интерпретира командата set
class SetCommand : public Command
{
public:
    void interpret(std::istream& is, char& next, Parser& object);
};