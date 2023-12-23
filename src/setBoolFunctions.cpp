#include "setBoolFunctions.hpp"
#include <sstream>

void setBool(std::istream &is, char &next, Parser::Node *temp, Parser &object)
{
    temp->value = setBoolHelper(is, next, object);
    object.arr.push_back(temp);
}

BoolValue *setBoolHelper(std::istream &is, char &next, Parser &object)
{
    is.get();
    std::string exp;
    getline(is, exp);
    std::stringstream expression(exp);
    std::string res = infixToRPN(expression);
    std::stringstream RPexpression(res);
    return new BoolValue(RPNeval(RPexpression, object));
}