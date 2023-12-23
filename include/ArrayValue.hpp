#pragma once
#include "BaseValue.hpp"
#include <vector>

// Клас ArrayValue който представлява променливи от тип std::vector<BaseValue*>, наследник на BaseValue
class ArrayValue : public BaseValue
{
private:
    std::vector<BaseValue *> value;
private:
    void copy(const ArrayValue &other);
    void destroy();
public:
    ArrayValue();
    ArrayValue(const ArrayValue &other);
    ArrayValue &operator=(const ArrayValue &other);
    ~ArrayValue();
    ArrayValue *clone();
    void addElement(BaseValue *element);
    int getSize() const;
    void print() const;
    BaseValue *getElementByIndex(int index);
};
