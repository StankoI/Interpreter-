#include "setNumFunctions.hpp"
#include <sstream>

void setNum(std::istream &is, char &next, Parser::Node *temp, Parser &object)
{
    temp->value = setNumHelper(is, next, object);
    object.arr.push_back(temp);
}

NumValue *setNumHelper(std::istream &is, char &next, Parser &object)
{
    std::string exp;
    getline(is, exp);
    // if (exp[0] == '-') //! za rabota sus otricatelni chisla
    // {
    //     exp = "0" + exp;
    // }
    std::stringstream expression(exp);

    char newNext = expression.peek();

    std::string firstWord;

    SpaceRemover(expression, newNext);

    if (newNext == '(')
    {
        Expression *t = parseExpression(expression, object);
        
        return new NumValue(t->eval());
    }

    while (newNext != ' ' && newNext != '(' && newNext != ';')
    {
        // std::cout << "here ";
        firstWord += newNext;
        expression.get();
        newNext = expression.peek();
    }

    if (firstWord == "if")
    {
        expression.seekg(0);
        Expression *t = parseExpression(expression, object);
        // t->eval();
        return new NumValue(t->eval());
    }

    //! ako se scupi nqkude tuk e problema

    expression.seekg(0);

    next = is.peek();
    std::string res = infixToRPN(expression);
    std::stringstream RPexpression(res);
    return new NumValue(RPNeval(RPexpression, object));
}