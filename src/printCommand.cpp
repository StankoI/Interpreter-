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

    std::string tempKey;
    while (next != ';')
    {
        tempKey += next;
        is.get();
        next = is.peek();
    }

    // std::string exp = getKey(is, next);
    std::string exp = tempKey;
    typename ::Parser::Node *tempNode = object.find(exp);
    if (tempNode)
    {
        tempNode->value->print();
        std::cout << '\n';
        std::string garbige;
        getline(is,garbige);
        next = is.peek();
        return;
    }
    
    exp += ";";
    std::stringstream expression(exp);
    std::stringstream RPexpression(infixToRPN(expression));
    // std::stringstream expression(exp);
    std::cout << RPNeval(RPexpression, object) << '\n';
    std::string garbige;
    getline(is,garbige);
    next = is.peek();
}
