#pragma once
#include "EvalFunctions.hpp"

class Command
{
public:
    virtual void interpret(std::istream& is, char& next, Parser& object) = 0;
};