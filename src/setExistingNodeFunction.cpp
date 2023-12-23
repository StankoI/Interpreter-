#include "setExistingNodeFunction.hpp"

void setExistingNode(Parser::Node *existingNode, std::istream &is, char &next, Parser &object)
{
    removeEqualSign(is, next);

    SpaceRemover(is, next);

    if (next == ':')
    {
        if (existingNode->type != Parser::BOOL)
        {
            throw "trying to set different types value";
        }

        delete existingNode->value;
        existingNode->value = setBoolHelper(is, next, object);
        return;
    }
    if (next == '\"')
    {
        if (existingNode->type != Parser::STRING)
        {
            throw "trying to set different types value";
        }

        delete existingNode->value;
        existingNode->value = setStringHelper(is, next, object);
        return;
    }
    if (next == '[')
    {
        if (existingNode->type != Parser::ARRAY)
        {
            throw "trying to set different types value";
        }

        delete existingNode->value;
        existingNode->value = setArrayHelper(is, next, object);
        return;
    }

    if (existingNode->type != Parser::NUM)
    {
        throw "trying to set different types value";
    }
    delete existingNode->value;
    existingNode->value = setNumHelper(is, next, object);
    return;
}