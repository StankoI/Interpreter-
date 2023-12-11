#pragma once
#include "NumValue.hpp"
#include "StringValue.hpp"
#include "BoolValue.hpp"
#include "ArrayValue.hpp"
#include <string>
#include <iostream>

class Tokenizer
{
    public:
    enum Token_type{OPEN_BRACK, CLOSE_BRACK, OPERATOR, NUMBER, CHAR ,STR, STOP_SYMBOL};

    struct Token
    {
        Token_type type;
        char symbol;
        BaseValue* value;
        std::string keyword;
    };
    
};



void SpaceRemover(std::istream &is, char &next);

std::istream& operator>>(std::istream&, Tokenizer::Token&);
std::ostream& operator<<(std::ostream&, const Tokenizer::Token&);
std::ifstream& operator>>(std::ifstream& is, Tokenizer::Token& t);