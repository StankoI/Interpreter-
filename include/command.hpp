#pragma once
#include "setExistingNodeFunction.hpp"
/// Интерфейсен клас за команди който се наследява от всички команди за интерпретиране на езика
class Command
{
public:
    virtual void interpret(std::istream& is, char& next, Parser& object) = 0;
};