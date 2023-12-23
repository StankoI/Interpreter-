#include "Parser.hpp"
#include <sstream>
#include <stack>
#include <cassert>
#include <functional>
//todo change the name of this class
Parser::Parser()
{
    this->arr.push_back(new Node{"AZIS",new NumValue(69),Parser::NUM});

    this->specialWords.insert("if");
    this->specialWords.insert("then");
    this->specialWords.insert("else");
    this->specialWords.insert("AZIS");
}


typename ::Parser::Node *Parser::find(std::string key)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (key == arr[i]->key)
        {
            return arr[i];
        }
    }
    return nullptr;
}

