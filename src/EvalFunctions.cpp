#include "EvalFunctions.hpp"
#include <cassert>
#include <sstream>
#include <stack>

//todo getKey and removeEqualSign function need own file 
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