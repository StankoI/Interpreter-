#pragma once
#include "NumValue.hpp"
#include "StringValue.hpp"
#include "BoolValue.hpp"
#include "ArrayValue.hpp"
#include <string>
#include <iostream>

/// Клас Tokenizer създава tokens от различни типове, използва се за оценяване на изрази
class Tokenizer
{
public:
    enum Token_type{OPEN_BRACK, CLOSE_BRACK, OPERATOR, NUMBER, CHAR ,STR, STOP_SYMBOL, IF, THEN, ELSE, FUNC};
    /// Структура за Tokens 
    struct Token
    {
        Token_type type;
        char symbol;
        BaseValue* value;
        std::string keyword;
    };

    Tokenizer(std::istream&);

    Token getNextToken();
    Token peekToken();

private:
    std::istream &in;
    Token *peeked;
    
};
///Функция която премахва празните пространства в поток
void SpaceRemover(std::istream &is, char &next);

std::istream& operator>>(std::istream&, Tokenizer::Token&);
std::ostream& operator<<(std::ostream&, const Tokenizer::Token&);
std::ifstream& operator>>(std::ifstream& is, Tokenizer::Token& t);