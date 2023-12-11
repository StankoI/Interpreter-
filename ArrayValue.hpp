#pragma once
#include "BaseValue.hpp"
#include <vector>

class ArrayValue: public BaseValue{
    private:
    std::vector<BaseValue* > value;

    void copy(const ArrayValue& other);

    void destroy();

    public:

    ArrayValue();

    ArrayValue(const ArrayValue& other);

    ArrayValue& operator=(const ArrayValue& other);

    ~ArrayValue();

    ArrayValue* clone();

    void addElement(BaseValue* element);

    int getSize() const;

    void print() const;

    BaseValue* getElementByIndex(int index);

};

