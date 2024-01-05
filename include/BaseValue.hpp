#pragma once

///Интерфейсен клас за типовете на езика, който да бъде наследен от други класове.
class BaseValue
{   
public:
    virtual ~BaseValue() = default;
    virtual BaseValue* clone() = 0;
    virtual void print() const = 0;
};