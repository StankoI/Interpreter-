#pragma once
#include "setExistingNodeFunction.hpp"

class Command
{
public:
    virtual void interpret(std::istream& is, char& next, Parser& object) = 0;
};