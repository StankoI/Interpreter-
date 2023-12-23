#include "setStringFunctions.hpp"

void setString(std::istream &is, char &next, Parser::Node *temp, Parser &object)
{
    temp->value = setStringHelper(is, next, object);
    object.arr.push_back(temp);
}

StringValue *setStringHelper(std::istream &is, char &next, Parser &object)
{
    is.get();
    std::string exp;
    getline(is, exp, '\"');
    is.get(); // remove "
    is.get(); // remove ;
    next = is.peek();
    return new StringValue(exp);
}