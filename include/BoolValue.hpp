#pragma once
#include "BaseValue.hpp"

/// Клас BoolValue който представлява променливи от тип bool, наследник на BaseValue
class BoolValue : public BaseValue
{
private:
    bool value;
public:
    BoolValue(bool _value);
    ~BoolValue();
    bool getValue() const;
    void setValue(bool newVal);
    BoolValue *clone();
    void print() const;
};
