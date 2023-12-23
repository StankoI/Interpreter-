#pragma once
#include "setBoolFunctions.hpp"
#include "setNumFunctions.hpp"
#include "setStringFunctions.hpp"
//class name ArraySetter 
void setArray(std::istream &is, char &next, Parser::Node *temp, Parser &object);

ArrayValue *setArrayHelper(std::istream &is, char &next, Parser &object);