#pragma once
#include "EvalFunctions.hpp"
/// функция за set-ване на променлива от тип Bool
void setBool(std::istream &is, char &next, Parser::Node *temp, Parser &object);
/// помощна функция за set-ване на променлива от тип Bool, преизползва се на няколко места
BoolValue *setBoolHelper(std::istream &is, char &next, Parser &object);