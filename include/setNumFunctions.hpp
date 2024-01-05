#pragma once
#include "EvalFunctions.hpp"
/// функция за set-ване на променлива от тип Num
void setNum(std::istream &is, char &next, Parser::Node *temp, Parser &object);
/// помощна функция за set-ване на променлива от тип Num, преизползва се на няколко места
NumValue *setNumHelper(std::istream &is, char &next, Parser &object);