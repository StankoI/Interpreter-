#pragma once
#include "BaseValue.hpp"
#include <string>

/// Клас StringValue който представлява променливи от тип std::string, наследник на BaseValue
class StringValue : public BaseValue
{
private:
    std::string value;
public:
    StringValue(std::string _value);
    ~StringValue();
    std::string getValue() const;
    void setValue(std::string newVal);
    StringValue *clone();
    void print() const;
};