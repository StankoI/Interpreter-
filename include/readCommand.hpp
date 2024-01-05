#pragma once
#include "command.hpp"

/// клас ReadCommand, наследник на Command който override-ва функцията interpret, като интерпретира командата read
class ReadCommand : public Command
{
public:
    void interpret(std::istream& is, char& next, Parser& object);
};