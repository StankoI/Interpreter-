#include "EvalFunctions.hpp"
#include <cassert>
#include <sstream>
#include <stack>

void setNum(std::istream &is, char &next, Parser::Node *temp, Parser &object)
{
    temp->value = setNumHelper(is, next, object);
    object.arr.push_back(temp);
}

void setBool(std::istream &is, char &next, Parser::Node *temp, Parser &object)
{
    temp->value = setBoolHelper(is, next, object);
    object.arr.push_back(temp);
}

void setString(std::istream &is, char &next, Parser::Node *temp, Parser &object)
{
    temp->value = setStringHelper(is, next, object);
    object.arr.push_back(temp);
}

void setArray(std::istream &is, char &next, Parser::Node *temp, Parser &object)
{
    ArrayValue *arrayVal = dynamic_cast<ArrayValue *>(temp->value);
    temp->value = setArrayHelper(is, next, object);
    is.get();
    object.arr.push_back(temp);
}

NumValue *setNumHelper(std::istream &is, char &next, Parser &object)
{
    std::string exp;
    getline(is, exp);
    // if (exp[0] == '-') //! za rabota sus otricatelni chisla
    // {
    //     exp = "0" + exp;
    // }
    std::stringstream expression(exp);

    char newNext = expression.peek();

    std::string firstWord;

    SpaceRemover(expression, newNext);

    if (newNext == '(')
    {
        Expression *t = parseExpression(expression, object);
        
        return new NumValue(t->eval());
    }

    while (newNext != ' ' && newNext != '(' && newNext != ';')
    {
        // std::cout << "here ";
        firstWord += newNext;
        expression.get();
        newNext = expression.peek();
    }

    if (firstWord == "if")
    {
        expression.seekg(0);
        Expression *t = parseExpression(expression, object);
        // t->eval();
        return new NumValue(t->eval());
    }

    //! ako se scupi nqkude tuk e problema

    expression.seekg(0);

    next = is.peek();
    std::string res = infixToRPN(expression);
    std::stringstream RPexpression(res);
    return new NumValue(RPNeval(RPexpression, object));
}

BoolValue *setBoolHelper(std::istream &is, char &next, Parser &object)
{
    is.get();
    std::string exp;
    getline(is, exp);
    std::stringstream expression(exp);
    std::string res = infixToRPN(expression);
    std::stringstream RPexpression(res);
    return new BoolValue(RPNeval(RPexpression, object));
}

StringValue *setStringHelper(std::istream &is, char &next, Parser &object)
{
    is.get();
    std::string exp;
    getline(is, exp, '\"');
    is.get(); // remove "
    is.get(); // remove ;
    next = is.peek();
    return new StringValue(exp);
}

ArrayValue *setArrayHelper(std::istream &is, char &next, Parser &object)
{
    is.get();
    next = is.peek();
    ArrayValue *arrayVal = new ArrayValue;
    while (next != ']')
    {
        if (next == '\"')
        {
            is.get();
            std::string exp;
            getline(is, exp, '\"');
            is.get(); // remove "
            StringValue *el = new StringValue(exp);
            // todo delete
            arrayVal->addElement(el);
            
            next = is.peek();
        }
        else if (next == ':')
        {
            is.get();
            std::string exp;
            getline(is, exp, ',');
            exp += ";";
            std::stringstream expression(exp);
            std::string res = infixToRPN(expression);
            std::stringstream RPexpression(res);
            BoolValue *resVal = new BoolValue(RPNeval(RPexpression, object));
            arrayVal->addElement(resVal);
            next = is.peek();
        }
        else if (next == '[')
        {
            arrayVal->addElement(setArrayHelper(is, next, object));
           
            is.get(); //* skip ','
            next = is.peek();
            // std::cout << next;
        }
        else
        {
            std::string exp;
            getline(is, exp, ',');
            exp += ";";
            std::stringstream expression(exp);
            std::string res = infixToRPN(expression);
            std::stringstream RPexpression(res);
            NumValue *resVal = new NumValue(RPNeval(RPexpression, object));
            arrayVal->addElement(resVal);
            next = is.peek();
        }
    }
    is.get();
    return arrayVal;
}

void setExistingNode(Parser::Node *existingNode, std::istream &is, char &next, Parser &object)
{
    removeEqualSign(is, next);

    SpaceRemover(is, next);

    if (next == ':')
    {
        if (existingNode->type != Parser::BOOL)
        {
            throw "trying to set different types value";
        }

        delete existingNode->value;
        existingNode->value = setBoolHelper(is, next, object);
        return;
    }
    if (next == '\"')
    {
        if (existingNode->type != Parser::STRING)
        {
            throw "trying to set different types value";
        }

        delete existingNode->value;
        existingNode->value = setStringHelper(is, next, object);
        return;
    }
    if (next == '[')
    {
        if (existingNode->type != Parser::ARRAY)
        {
            throw "trying to set different types value";
        }

        delete existingNode->value;
        existingNode->value = setArrayHelper(is, next, object);
        return;
    }

    if (existingNode->type != Parser::NUM)
    {
        throw "trying to set different types value";
    }
    delete existingNode->value;
    existingNode->value = setNumHelper(is, next, object);
    return;
}

std::string getKey(std::istream& is, char& next)
{
    std::string tempKey;
    while (next != ' ' && next != '=' && next != '\n' && next != ';')
    {
        tempKey += next;
        is.get();
        next = is.peek();
    }
    return tempKey;
}

void removeEqualSign(std::istream& is,char& next)
{
    while (next != '=')
    {
        is.get();
        next = is.peek();
    }

    is.get(); 
    next = is.peek();
}

std::string infixToRPN(std::istream &in)
{
    Tokenizer::Token t;
    in >> t;

    std::vector<Tokenizer::Token> output;
    std::stack<Tokenizer::Token> shuntingYard;

    while (t.type != Tokenizer::STOP_SYMBOL)
    {
        if (t.type == Tokenizer::NUMBER)
        {
            output.push_back(t);
        }
        else if (t.type == Tokenizer::STR)
        {
            output.push_back(t);
        }
        else if (t.type == Tokenizer::OPEN_BRACK)
        {
            shuntingYard.push(t);
        }
        else if (t.type == Tokenizer::CLOSE_BRACK)
        {
            assert(shuntingYard.size() > 0);
            while (shuntingYard.top().type != Tokenizer::OPEN_BRACK)
            {
                assert(shuntingYard.size() > 0);
                output.push_back(shuntingYard.top());
                shuntingYard.pop();
            }
            shuntingYard.pop();
        }
        else if (t.type == Tokenizer::OPERATOR)
        {
            while (shuntingYard.size() > 0 &&
                   shuntingYard.top().type != Tokenizer::OPEN_BRACK &&
                   priority(shuntingYard.top().symbol) >= priority(t.symbol))
            {
                Tokenizer::Token waiting;
                output.push_back(shuntingYard.top());
                shuntingYard.pop();
            }
            shuntingYard.push(t);
        }

        in >> t;
    }

    while (shuntingYard.size() > 0)
    {
        output.push_back(shuntingYard.top());
        shuntingYard.pop();
    }

    std::stringstream rpn;

    for (Tokenizer::Token tk : output)
    {
        // std::cout << t.keyword << " ";
        rpn << tk << " ";
    }

    return rpn.str() + ";";
}

double RPNeval(std::istream &in, Parser& object)
{
    Tokenizer::Token t;
    in >> t;

    std::stack<double> s;

    while (t.type != Tokenizer::STOP_SYMBOL)
    {
        assert(t.type == Tokenizer::NUMBER || t.type == Tokenizer::OPERATOR || t.type == Tokenizer::STR);
        if (t.type == Tokenizer::NUMBER)
        {
            NumValue *ktmp = dynamic_cast<NumValue *>(t.value);
            s.push(ktmp->getValue());
        }
        else if (t.type == Tokenizer::STR) //!
        {
            bool found = 0;
            for (std::size_t i = 0; i < object.arr.size(); i++)
            {
                if (t.keyword == object.arr[i]->key)
                {
                    assert(object.arr[i]->type == Parser::NUM);
                    t.value = object.arr[i]->value;
                    //! eventualno problem sus smesena pamet
                    found = 1;
                }
            }
            if (found == 0)
            {
                throw "undefined symbol";
            }
            else
            {
                NumValue *tmp = dynamic_cast<NumValue *>(t.value);
                s.push(tmp->getValue());
            }
            // s.push(t.value);
        }
        else
        { // t.type == Tokenizer::OPERATOR
            assert(s.size() > 1);
            double right = s.top();
            s.pop();
            double left = s.top();
            s.pop();
            s.push(fn(t.symbol)(left, right));
        }
        in >> t;
    }

    assert(s.size() == 1);
    return s.top();
}