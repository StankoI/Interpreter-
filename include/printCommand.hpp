#pragma once
#include "command.hpp"

/// клас PrintCommand, наследник на Command който override-ва функцията interpret, като интерпретира командата print
class PrintCommand : public Command
{
public:
    void interpret(std::istream& is, char& next, Parser& object);
};