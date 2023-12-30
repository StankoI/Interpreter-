#pragma once
#include "Tokenizer.hpp"
#include <functional>

class Expression
{
public:
    virtual double eval() const = 0;
    virtual Expression *clone() = 0;
    virtual ~Expression() = default;
};

class ExprConst : public Expression
{
private:
    NumValue *val;

public:
    ExprConst(double _val);
    double eval() const;
    ExprConst *clone();
};

class ExprArith : public Expression
{
private:
    std::function<double(double, double)> opfn;
    char symbol;
    Expression *left, *right;

public:
    ExprArith(char _op, Expression *_left, Expression *_right);
    ExprArith(const ExprArith &);
    double eval() const;
    ExprArith *clone();
    ~ExprArith();
};

class ExprIf : public Expression
{
private:
    Expression *cond, *iftrue, *iffalse;

public:
    ExprIf(Expression *_cond, Expression *_iftrue, Expression *_iffalse);
    ExprIf(const ExprIf &);
    double eval() const;
    ExprIf *clone();
    ~ExprIf();
};

std::function<double(double, double)> fn(char c);

int priority(char op);