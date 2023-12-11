#include "NumValue.hpp"
#include <iostream>

NumValue::NumValue(double _value):value(_value){}

NumValue* NumValue::clone()
{
    return new NumValue(*this);
}

double NumValue::getValue() const
{
    return this->value;
}

void NumValue::setValue(double newVal)
{
    this->value = newVal;
}   

NumValue::~NumValue(){}

void NumValue::print() const
{
    std::cout << this->value;
}

