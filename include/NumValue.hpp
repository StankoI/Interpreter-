#pragma once
#include "BaseValue.hpp"
#include <fstream>

/// Клас NumValue който представлява променливи от тип double, наследник на BaseValue
class NumValue : public BaseValue
{
private:
    double value;
public:
    NumValue(double _value);
    ~NumValue();
    NumValue *clone();
    double getValue() const;
    void setValue(double newVal);
    void print() const;
};
