#pragma once
#include "EvalFunctions.hpp"
/// функция за set-ване на променлива от тип String
void setString(std::istream &is, char &next, Parser::Node *temp, Parser &object);
/// помощна функция за set-ване на променлива от тип String, преизползва се на няколко места
StringValue *setStringHelper(std::istream &is, char &next, Parser &object);