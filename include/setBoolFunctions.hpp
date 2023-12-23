#pragma once
#include "EvalFunctions.hpp"

void setBool(std::istream &is, char &next, Parser::Node *temp, Parser &object);

BoolValue *setBoolHelper(std::istream &is, char &next, Parser &object);