#include "BoolValue.hpp"
#include <fstream>
#include <iostream>

BoolValue::BoolValue(bool _value):value(_value){}

bool BoolValue::getValue() const
{
    return this->value;
}

void BoolValue::setValue(bool newVal)
{
    this->value = newVal;
}

BoolValue* BoolValue::clone()
{
    return new BoolValue(*this);
}

BoolValue::~BoolValue(){}

void BoolValue::print() const
{
    std::cout << std::boolalpha << this->value;
}