#pragma once
#include "BaseValue.hpp"
#include <fstream>

class NumValue : public BaseValue
{
    private:
    double value;

    public:

    NumValue(double _value);

    NumValue* clone();

    double getValue() const;

    void setValue(double newVal);

    ~NumValue();

    void print() const;
};

