#pragma once
#include "Parser.hpp"
#include <vector>

/// функция която връща параметъра на функцията който е заграден в "[]" 
std::string getPar(std::string expr);
/// Връща ключа, име на променлива, или име на фунция, използва се при set-ване на променливи и оценяване на функции
std::string getKey(std::istream& is, char& next);

/// Функции за построяване на дърво на извода, по подаден поток
Expression *parseExpression(std::istream &is, Parser &object);
Expression *parseExpression(Tokenizer &tokens, Parser &object);
Expression *parseConst(Tokenizer &tokens, Parser &object);
Expression *parseIfExpression(Tokenizer &tokens, Parser &object);
Expression *parseParExpression(Tokenizer &tokens, Parser &object);