#pragma once
#include "EvalFunctions.hpp"
//class name NumSetter
void setNum(std::istream &is, char &next, Parser::Node *temp, Parser &object);

NumValue *setNumHelper(std::istream &is, char &next, Parser &object);