#pragma once
#include "EvalFunctions.hpp"

void setString(std::istream &is, char &next, Parser::Node *temp, Parser &object);

StringValue *setStringHelper(std::istream &is, char &next, Parser &object);