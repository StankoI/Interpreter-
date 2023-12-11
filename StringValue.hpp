#pragma once
#include "BaseValue.hpp"
#include <string>

class StringValue: public BaseValue
{
    private:
    std::string value;

    public:

    StringValue(std::string _value);

    std::string getValue() const;

    void setValue(std::string newVal);

    StringValue* clone();

    ~StringValue();

    void print() const;
    
};

