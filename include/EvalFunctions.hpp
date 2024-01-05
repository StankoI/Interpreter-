#pragma once
#include "ExprTreeBuilding.hpp"

/// Функция която оценява израз записан в reverse polish notation(RPN) 
double RPNeval(std::istream &in, Parser& object);

/// Функция която превръща израз от инфиксен в RPN израз, като използва shunting yard алгоритъм 
std::string infixToRPN(std::istream &in);

/// Функция която премахва знака '=', изполва се при set-ването на променливи  
void removeEqualSign(std::istream& is,char& next);