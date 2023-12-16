#include "ArrayValue.hpp"
#include <vector>
#include <fstream>
#include <iostream>

ArrayValue::ArrayValue(){}

void ArrayValue::copy(const ArrayValue &other)
{
    for(int i = 0; i < other.value.size(); i++)
    {
        this->value.push_back(other.value[i]->clone());
    }
}

void ArrayValue::destroy()
{
    for(int i = 0; i < this->value.size(); i++)
    {
        delete this->value[i];
        this->value[i] = nullptr;
    }
}

ArrayValue::ArrayValue(const ArrayValue &other)
{
    this->copy(other);
}

ArrayValue& ArrayValue::operator=(const ArrayValue &other)
{
    if(this != &other)
    {
        this->destroy();
        this->copy(other);
    }

    return *this;
}

ArrayValue::~ArrayValue()
{
    this->destroy();
}

ArrayValue* ArrayValue::clone() 
{
    return new ArrayValue(*this);
}

void ArrayValue::addElement(BaseValue* element)
{
    this->value.push_back(element->clone());
}

int ArrayValue::getSize() const
{
    return this->value.size();
}

void ArrayValue::print() const
{
    std::cout << "[";
    for(int i = 0; i < this->value.size(); i++)
    {
        this->value[i]->print();
        if(i < this->getSize()-1)
        {
            std::cout << ',';
        }
    }
    std::cout << "]";
}

BaseValue* ArrayValue::getElementByIndex(int index)
{
    if(index >= this->value.size())
    {
        return nullptr;
    }
    return this->value[index];
}

