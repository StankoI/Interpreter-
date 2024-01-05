#pragma once
#include "command.hpp"
/// клас FuncCommand, наследник на Command който override-ва функцията interpret, като интерпретира фунцкии
class FuncCommand : public Command
{
public:
    void interpret(std::istream& is, char& next, Parser& object);
};