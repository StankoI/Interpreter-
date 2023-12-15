#include "ExprTree.hpp"
#include <cmath>
#include <iostream>
#include <cassert>

std::function<double(double, double)> fn(char c)
{
    switch (c)
    {
    case '+':
        return [](double x, double y) -> double
        { return x + y; };
    case '-':
        return [](double x, double y) -> double
        { return x - y; };
    case '*':
        return [](double x, double y) -> double
        { return x * y; };
    case '/':
        return [](double x, double y) -> double
        { return x / y; };
    case '>':
        return [](double x, double y) -> double
        { return x > y; };
    case '<':
        return [](double x, double y) -> double
        { return x < y; };
    case '=':
        return [](double x, double y) -> double
        { return x == y; };
    case '^':
        return [](double x, double y) -> double
        {   //std::cout << " test: "<< x << " " << y << " " << pow(x,y);
            return std::pow(x,y);};
    default:
        assert(false);
    }

    return [](int, int) -> int
    {assert(false);return -1; };
}

int priority(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 10;
    case '*':
    case '/':
        return 20;
    case '<':
    case '>':
    case '=':
        return 5;
    case '^':
        return 30;
    default:
        assert(false);
    }
    return -1;
}


ExprConst::ExprConst(double _val):val(new NumValue(_val)){}

double ExprConst::eval() const
{
    return val->getValue();
}

ExprConst* ExprConst::clone()
{
    return new ExprConst(*this);
}

ExprArith::ExprArith(const ExprArith &other)
{
    opfn = other.opfn;
    symbol = other.symbol;
    left = other.left->clone();
    right = other.right->clone();
}


ExprArith::ExprArith(char _op, Expression *_left, Expression *_right)
{
    opfn = fn(_op);
    symbol = _op;

    left = _left->clone();
    right = _right->clone();
}

double ExprArith::eval() const
{
    return opfn(left->eval(), right->eval());
}

ExprArith* ExprArith::clone()
{
    return new ExprArith(*this);
}

ExprArith::~ExprArith()
{
    delete left;
    delete right;
}

ExprIf::ExprIf(Expression *_cond, Expression *_iftrue, Expression *_iffalse)
                            :cond(_cond), iftrue(_iftrue), iffalse(_iffalse){}


ExprIf::ExprIf(const ExprIf &other)
{
    cond = other.cond->clone();
    iftrue = other.iftrue->clone();
    iffalse = other.iffalse->clone();
}

double ExprIf::eval() const
{
    if(std::abs(cond->eval()) > 0.005)
    {
        return iftrue->eval();
    }

    return iffalse->eval();
}

ExprIf* ExprIf::clone()
{
    return new ExprIf(*this);
}

ExprIf::~ExprIf()
{
    delete cond;
    delete iftrue;
    delete iffalse;
}

//! ot tuka nadolu vsichko trqbva da ide v parser

// Expression* parseExpression(Tokenizer &tokens);

