#pragma once
#include "Tokenizer.hpp"
#include <functional>

/// Интерфейсен клас за дърво на извода, който се наследява от изводите на дървото
class Expression
{
public:
    virtual double eval() const = 0;
    virtual Expression *clone() = 0;
    virtual ~Expression() = default;
};

/// Клас за връх на дърво, чиято стойност е константа 
class ExprConst : public Expression
{
private:
    NumValue *val;

public:
    ExprConst(double _val);
    double eval() const;
    ExprConst *clone();
};

/// Клас за връх на дърво, чиято стойност е аритметичен израз заграден в скоби
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

/// Клас за връх на дърво, чиято стойност е условен оператор if
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

/// функция за оценяване на израз която получава 2 параметъра и оператор
std::function<double(double, double)> fn(char c);
/// функция която получава оператор и връща неговият приоритет за оценка, като с 30 са операторите с най-висок приоритет и с 5 са операторите с най-нисък приоритет 
int priority(char op);