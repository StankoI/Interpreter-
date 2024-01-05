#include "funcCommand.hpp"
#include <sstream>

void FuncCommand::interpret(std::istream &is, char &next, Parser &object)
{
    SpaceRemover(is, next);

    Parser::Func *temp = new Parser::Func;
    // temp->type = Parser::FUNC;

    std::string tempKey = getKey(is, next); 
    temp->key = tempKey;
    SpaceRemover(is, next);

    is.get(); //* remove '['
    next = is.peek();

    temp->varible = getKey(is, next);
    
    is.get();
    next = is.peek();

    removeEqualSign(is, next);
    SpaceRemover(is, next);

    getline(is, temp->body);
    next = is.peek();

    object.functions.push_back(temp);
}
