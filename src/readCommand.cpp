#include "readCommand.hpp"
#include <sstream>

void ReadCommand::interpret(std::istream& is, char& next, Parser& object)
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

    //!!!това не бачка;
    Parser::Node* existingNode = object.find(tempKey); 
    if(existingNode != nullptr)
    {
        setExistingNode(existingNode,is,next,object);
        return;
    }
    //!

    temp->key = tempKey;

    std::cout << ">";
    std::string exp;
    getline(std::cin, exp);

    exp += ';';

    is.get(); 
    next = is.peek();

    std::stringstream exprestion(exp);

    char newNext = exprestion.peek(); 

    SpaceRemover(exprestion, newNext);

    if (newNext == ':')
    {
        temp->type = Parser::BOOL;
        setBool(exprestion, newNext, temp,object);
        return;
    }
    if (newNext == '\"')
    {
        temp->type = Parser::STRING;
        setString(exprestion, newNext, temp,object);
        return;
    }
    if (newNext == '[')
    {
        temp->type = Parser::ARRAY;
        setArray(exprestion, newNext, temp,object);
        return;
    }
    
    temp->type = Parser::NUM;
    setNum(exprestion, newNext, temp,object);
    return;
}