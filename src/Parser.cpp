#include "Parser.hpp"
#include <sstream>
#include <stack>
#include <cassert>
#include <functional>
//todo change the name of this class
Parser::Parser()
{
    this->arr.push_back(new Node{"AZIS",new NumValue(69),Parser::NUM});
    this->arr.push_back(new Node{"GEORGI",new NumValue(420),Parser::NUM});
    this->arr.push_back(new Node{"true",new BoolValue(1),Parser::BOOL});
    this->arr.push_back(new Node{"false",new BoolValue(0),Parser::BOOL});


    this->specialWords.insert("if");
    this->specialWords.insert("then");
    this->specialWords.insert("else");
    this->specialWords.insert("AZIS");
    this->specialWords.insert("GEORGI");
    this->specialWords.insert("true");
    this->specialWords.insert("false");

}


typename ::Parser::Node *Parser::find(const std::string& key)
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

typename ::Parser::Func *Parser::findFunction(const std::string& key)
{
    for (int i = 0; i < functions.size(); i++)
    {
        if (key == functions[i]->key)
        {
            return functions[i];
        }
    }
    return nullptr;
}

Parser::Parser(const Parser& other)
{
    this->copy(other);
}

Parser& Parser::operator=(const Parser& other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

Parser::~Parser()
{
    destroy();
}

void Parser::destroy()
{
    for(int i = 0; i < this->arr.size() ;i++)
    { 
        delete this->arr[i];
    }

    for(int i = 0; i < this->functions.size();i++)
    {
        delete this->functions[i];
    }
}

Parser::Node::~Node()
{
    delete this->value;
}

void Parser::copy(const Parser& other)
{
    for(int i = 0; i < other.arr.size(); i++)
    {
        this->arr.push_back(new Node{other.arr[i]->key,other.arr[i]->value->clone(),other.arr[i]->type});
    }
    for(int i = 0; i < other.functions.size(); i++)
    {
        this->functions.push_back(new Func(*other.functions[i]));
    }
}

// Parser::Func::Func(const Func& other)
// {

// }
