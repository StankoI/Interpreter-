#include "StringValue.hpp"
#include <string>
#include <iostream>

StringValue::StringValue(std::string _value):value(_value){}

std::string StringValue::getValue() const
{
    return this->value;
}

void StringValue::setValue(std::string newVal)
{
    this->value = newVal;
}

StringValue* StringValue::clone()
{
    return new StringValue(*this);
}

StringValue::~StringValue(){}

void StringValue::print() const
{
    std::cout << this->value;
}