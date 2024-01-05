#pragma once
#include "setBoolFunctions.hpp"
#include "setNumFunctions.hpp"
#include "setStringFunctions.hpp"
/// функция за set-ване на променлива от тип Array
void setArray(std::istream &is, char &next, Parser::Node *temp, Parser &object);
/// помощна функция за set-ване на променлива от тип Array, преизползва се на няколко места
ArrayValue *setArrayHelper(std::istream &is, char &next, Parser &object);