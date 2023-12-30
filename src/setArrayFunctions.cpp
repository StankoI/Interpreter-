#include "setArrayFunctions.hpp"
#include <sstream>

void setArray(std::istream &is, char &next, Parser::Node *temp, Parser &object)
{
    ArrayValue *arrayVal = dynamic_cast<ArrayValue *>(temp->value);
    temp->value = setArrayHelper(is, next, object);
    is.get();
    object.arr.push_back(temp);
}

ArrayValue *setArrayHelper(std::istream &is, char &next, Parser &object)
{
    is.get();
    next = is.peek();
    ArrayValue *arrayVal = new ArrayValue;
    while (next != ']')
    {
        if (next == '\"')
        {
            is.get();
            std::string exp;
            getline(is, exp, '\"');
            is.get(); // remove "
            StringValue *el = new StringValue(exp);
            // todo delete
            arrayVal->addElement(el);
            delete el;
            
            next = is.peek();
        }
        else if (next == ':')
        {
            is.get();
            std::string exp;
            getline(is, exp, ',');
            exp += ";";
            std::stringstream expression(exp);
            std::string res = infixToRPN(expression);
            std::stringstream RPexpression(res);
            BoolValue *resVal = new BoolValue(RPNeval(RPexpression, object));
            // todo delete
            arrayVal->addElement(resVal);
            delete resVal;
            next = is.peek();
        }
        else if (next == '[')
        {
            ArrayValue* resVal = setArrayHelper(is, next, object);
            arrayVal->addElement(resVal);
            delete resVal;
           
            is.get(); //* skip ','
            next = is.peek();
            // std::cout << next;
        }
        else
        {
            std::string exp;
            getline(is, exp, ',');
            exp += ";";
            std::stringstream expression(exp);
            std::string res = infixToRPN(expression);
            std::stringstream RPexpression(res);
            NumValue *resVal = new NumValue(RPNeval(RPexpression, object));
            // todo delete
            arrayVal->addElement(resVal);
            delete resVal;
            next = is.peek();
        }
    }
    is.get();
    return arrayVal;
}