#include "ExprTreeBuilding.hpp"
#include <cassert>
#include <sstream>

std::string getKey(std::istream &is, char &next)
{
    std::string tempKey;
    while (next != ' ' && next != '=' && next != '\n' && next != ';' && next != '(' && next != ')' && next != ']' && next != '[')
    {
        tempKey += next;
        is.get();
        next = is.peek();
    }
    return tempKey;
}

std::string getPar(std::string expr)
{
    int i = 0;
    while (expr[i] != '[')
    {
        i++;
    }
    i++;
    std::string par = "";
    while (expr[i] != ']')
    {
        par += expr[i];
        i++;
    }
    return par;
}

double evalFunc(Tokenizer &tokens, Parser& object)
{
    std::stringstream expr(tokens.peekToken().keyword);
    char newNext = expr.peek();

    std::string key = getKey(expr, newNext);
    Parser::Func *tmp = object.findFunction(key);
    std::string parameter = getPar(tokens.peekToken().keyword);
    parameter += ';';
    std::stringstream parExpr(parameter);

    Expression *res = parseExpression(parExpr, object);
    
    // Parser scope(object);
    Parser scope = object;
    // scope = object;

    Parser::Node* existingPar = scope.find(tmp->varible);
    if(existingPar)
    {
        existingPar->value = new NumValue(res->eval());
    }
    else
    {
        Parser::Node* var = new Parser::Node{tmp->varible,new NumValue(res->eval()),Parser::NUM};
        scope.arr.insert(scope.arr.begin(), var);
    }

    std::stringstream bodyExpr(tmp->body);

    Expression *finalres = parseExpression(bodyExpr, scope);
    tokens.getNextToken();
    return finalres->eval();
}

Expression *parseExpression(std::istream &is, Parser &object)
{
    Tokenizer tokens(is);
    return parseExpression(tokens, object);
}

Expression *parseExpression(Tokenizer &tokens, Parser &object)
{
    if (tokens.peekToken().type == Tokenizer::IF)
    {
        return parseIfExpression(tokens, object);
    }
    if (tokens.peekToken().type == Tokenizer::NUMBER || tokens.peekToken().type == Tokenizer::STR || tokens.peekToken().type == Tokenizer::FUNC )
    {
        return parseConst(tokens, object);
    }
    if (tokens.peekToken().type == Tokenizer::OPEN_BRACK)
    {
        return parseParExpression(tokens, object);
    }

    throw "Syntax error. Unknown expression type";
    return nullptr;
}

Expression *parseConst(Tokenizer &tokens, Parser &object)
{
    assert(tokens.peekToken().type == Tokenizer::NUMBER || tokens.peekToken().type == Tokenizer::STR 
        || tokens.peekToken().type == Tokenizer::FUNC);

    if (tokens.peekToken().type == Tokenizer::STR)
    {
        Parser::Node *element = object.find(tokens.peekToken().keyword);
        if (!element)
        {
            throw "element does't exist";
        }

        if (element->type == Parser::NUM)
        {
            NumValue *tmp = dynamic_cast<NumValue *>(element->value);
            tokens.getNextToken();
            return new ExprConst(tmp->getValue());
        }
        else if (element->type == Parser::BOOL)
        {
            BoolValue *tmp = dynamic_cast<BoolValue *>(element->value);
            tokens.getNextToken();
            return new ExprConst(tmp->getValue());
        }
        else
        {
            throw "not a condition";
        }
    }

    if (tokens.peekToken().type == Tokenizer::FUNC) 
    {
        return new ExprConst(evalFunc(tokens, object));
    }

    NumValue *tmp = dynamic_cast<NumValue *>(tokens.getNextToken().value);

    return new ExprConst(tmp->getValue());
}

Expression *parseIfExpression(Tokenizer &tokens, Parser &object)
{
    assert(tokens.getNextToken().type == Tokenizer::IF);

    Expression *cond = parseExpression(tokens, object);

    assert(tokens.getNextToken().type == Tokenizer::THEN);

    
    if(cond->eval())
    {
        Expression *iftrue = parseExpression(tokens, object);

        assert(tokens.getNextToken().type == Tokenizer::ELSE);

        Expression *iffalse = nullptr;

        tokens.getNextToken();

        return new ExprIf(cond, iftrue, iffalse);
    } 
    if(!cond->eval())
    {
        Expression *iftrue = nullptr;

        while(tokens.peekToken().type != Tokenizer::ELSE)
        {
            tokens.getNextToken();
        }

        assert(tokens.getNextToken().type == Tokenizer::ELSE);

        Expression *iffalse = parseExpression(tokens, object);

        return new ExprIf(cond, iftrue, iffalse);
    }
    
    Expression *iftrue = parseExpression(tokens, object);

    assert(tokens.getNextToken().type == Tokenizer::ELSE);

    Expression *iffalse = parseExpression(tokens, object);

    return new ExprIf(cond, iftrue, iffalse);
}

Expression *parseParExpression(Tokenizer &tokens, Parser &object)
{
    assert(tokens.getNextToken().type == Tokenizer::OPEN_BRACK);

    Expression *left = parseExpression(tokens, object);

    assert(tokens.peekToken().type == Tokenizer::OPERATOR);
    char op = tokens.getNextToken().symbol;

    Expression *right = parseExpression(tokens, object);

    assert(tokens.getNextToken().type == Tokenizer::CLOSE_BRACK);

    return new ExprArith(op, left, right);
}