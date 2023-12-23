#include "printCommand.hpp"
#include <sstream>

void PrintCommand::interpret(std::istream &is, char &next, Parser &object)
{
    SpaceRemover(is, next);

    if (next == '\"')
    {
        is.get();
        next = is.peek();
        std::string exp;
        getline(is, exp, '\"');
        is.get(); // remove "
        is.get(); // remove ;
        next = is.peek();
        std::cout << exp << '\n';
        return;
    }
    std::string exp;
    getline(is, exp, ';');

    typename ::Parser::Node *tempNode = object.find(exp);
    if (tempNode)
    {
        tempNode->value->print();
        std::cout << '\n';
        return;
    }
    exp += ";";
    std::stringstream expression(exp);
    std::stringstream RPexpression(infixToRPN(expression));
    // std::stringstream expression(exp);
    std::cout << RPNeval(RPexpression, object) << '\n';
    is.get();
    next = is.peek();
}