#pragma once
#include "ExprTreeBuilding.hpp"
//todo getKey and removeEqualSign function need own file 

double RPNeval(std::istream &in, Parser& object);

std::string infixToRPN(std::istream &in);

void removeEqualSign(std::istream& is,char& next);