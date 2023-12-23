#include "ExprTreeBuilding.hpp"
#include <cassert>

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
    if (tokens.peekToken().type == Tokenizer::NUMBER || tokens.peekToken().type == Tokenizer::STR)
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
    assert(tokens.peekToken().type == Tokenizer::NUMBER || tokens.peekToken().type == Tokenizer::STR);

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

    NumValue *tmp = dynamic_cast<NumValue *>(tokens.getNextToken().value);

    return new ExprConst(tmp->getValue());
}

Expression *parseIfExpression(Tokenizer &tokens, Parser &object)
{
    assert(tokens.getNextToken().type == Tokenizer::IF);

    // std::cout << "keyword: " << tokens.peekToken().type;

    Expression *cond = parseExpression(tokens, object);

    assert(tokens.getNextToken().type == Tokenizer::THEN);

    Expression *iftrue = parseExpression(tokens, object);

    assert(tokens.getNextToken().type == Tokenizer::ELSE);

    Expression *iffalse = parseExpression(tokens, object);

    // std::cout << "token: " << tokens.peekToken().keyword;

    return new ExprIf(cond, iftrue, iffalse);
}

Expression *parseParExpression(Tokenizer &tokens, Parser &object)
{
    //(<left subexpr> <ope> <right subex>)

    assert(tokens.getNextToken().type == Tokenizer::OPEN_BRACK);

    //<left subexpr> <ope> <right subex>)
    Expression *left = parseExpression(tokens, object);

    //<ope> <right subex>)
    assert(tokens.peekToken().type == Tokenizer::OPERATOR);
    char op = tokens.getNextToken().symbol;

    //<right subex>)
    Expression *right = parseExpression(tokens, object);

    //)
    assert(tokens.getNextToken().type == Tokenizer::CLOSE_BRACK);

    return new ExprArith(op, left, right);
}