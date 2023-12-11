#pragma once
#include "BaseValue.hpp"

class BoolValue: public BaseValue
{
    private:
    bool value;

    public:

    BoolValue(bool _value);

    bool getValue() const;

    void setValue(bool newVal);

    BoolValue* clone();

    ~BoolValue();

    void print() const;

};
