#pragma once
#include "Parser.hpp"
#include <vector>

//! getKey i getPar ne ma im tuka mqstoto 
std::string getPar(std::string expr);
std::string getKey(std::istream& is, char& next);

Expression *parseExpression(std::istream &is, Parser &object);
Expression *parseExpression(Tokenizer &tokens, Parser &object);
Expression *parseConst(Tokenizer &tokens, Parser &object);
Expression *parseIfExpression(Tokenizer &tokens, Parser &object);
Expression *parseParExpression(Tokenizer &tokens, Parser &object);