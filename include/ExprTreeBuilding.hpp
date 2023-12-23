#pragma once
#include "Parser.hpp"

Expression *parseExpression(std::istream &is, Parser &object);
Expression *parseExpression(Tokenizer &tokens, Parser &object);
Expression *parseConst(Tokenizer &tokens, Parser &object);
Expression *parseIfExpression(Tokenizer &tokens, Parser &object);
Expression *parseParExpression(Tokenizer &tokens, Parser &object);