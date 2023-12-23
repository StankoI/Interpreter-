#pragma once
#include "ExprTreeBuilding.hpp"

//Set фyнкции
void setNum(std::istream &is, char &next, Parser::Node *temp, Parser &object);

void setBool(std::istream &is, char &next, Parser::Node *temp, Parser &object);

void setString(std::istream &is, char &next, Parser::Node *temp, Parser &object);

void setArray(std::istream &is, char &next, Parser::Node *temp, Parser &object);

void setExistingNode(Parser::Node *existingNode, std::istream &is, char &next, Parser &object);

std::string getKey(std::istream& is, char& next);

//Помощни функции за set-ване на изрази отделени за да могат да се преизползват
NumValue *setNumHelper(std::istream &is, char &next, Parser &object);

BoolValue *setBoolHelper(std::istream &is, char &next, Parser &object);

StringValue *setStringHelper(std::istream &is, char &next, Parser &object);

ArrayValue *setArrayHelper(std::istream &is, char &next, Parser &object);

//Функции за строене на дърво за израза 


double RPNeval(std::istream &in, Parser& object);

std::string infixToRPN(std::istream &in);

void removeEqualSign(std::istream& is,char& next);