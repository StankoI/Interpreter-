#include "setCommand.hpp"
#include <string>
#include <sstream>
#include <cassert>

void SetCommand::interpret(std::istream &is, char &next, Parser &object)
{
    //!
    SpaceRemover(is, next);
    Parser::Node *temp = new Parser::Node;

    std::string tempKey = getKey(is,next);
    
    auto it = object.specialWords.find(tempKey);
    if(it != object.specialWords.end())
    {
        throw "this words are SPECIAL";
    }

    Parser::Node *existingNode = object.find(tempKey); 
    if (existingNode != nullptr)
    {
        setExistingNode(existingNode, is, next, object);
        return;
    }
    //!

    temp->key = tempKey;

    removeEqualSign(is,next);

    SpaceRemover(is, next);

    if (next == ':')
    {
        temp->type = Parser::BOOL;
        setBool(is, next, temp, object);
        return;
    }
    if (next == '\"')
    {
        temp->type = Parser::STRING;
        setString(is, next, temp, object);
        return;
    }
    if (next == '[')
    {
        temp->type = Parser::ARRAY;
        setArray(is, next, temp, object);
        return;
    }

    temp->type = Parser::NUM;
    setNum(is, next, temp, object);
    return;
}