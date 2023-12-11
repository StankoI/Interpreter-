#include "Parser.hpp"
#include <sstream>
#include <stack>
#include <cassert>
#include <functional>

std::function<int(int, int)> fn(char c)
{
    switch (c)
    {
    case '+':
        return [](int x, int y) -> int
        { return x + y; };
    case '-':
        return [](int x, int y) -> int
        { return x - y; };
    case '*':
        return [](int x, int y) -> int
        { return x * y; };
    case '/':
        return [](int x, int y) -> int
        { return x / y; };
    case '>':
        return [](int x, int y) -> int
        { return x > y; };
    case '<':
        return [](int x, int y) -> int
        { return x < y; };
    case '=':
        return [](int x, int y) -> int
        { return x == y; };
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
    default:
        assert(false);
    }
    return -1;
}

void Parser::readFromFile(std::istream &is)
{
    {
        while (is)
        {
            char next = is.peek();
            SpaceRemover(is, next);

            std::string command;
            is >> command;
            next = is.peek();

            if (command == "set")
            {
                this->setCommandInterp(is, next);
            }
            else if (command == "print")
            {
                // std::cout << "cycling";
                this->printCommandInterp(is, next);
            }
            else if (command == "read")
            {
                this->readCommandInterp(is,next);
            }
        }
    }
}

void Parser::setCommandInterp(std::istream &is, char &next)
{
    SpaceRemover(is, next);
    Parser::Node *temp = new Parser::Node;

    std::string tempKey;
    while (next != ' ' && next != '=')
    {
        tempKey += next;
        is.get();
        next = is.peek();
    }

    temp->key = tempKey;

    while (next != '=')
    {
        is.get();
        next = is.peek();
    }

    is.get(); //* mahame ravnoto
    next = is.peek();

    SpaceRemover(is, next);

    if (next == ':')
    {
        temp->type = Parser::BOOL;
        this->setBool(is, next, temp);
        return;
    }
    if (next == '\"')
    {
        temp->type = Parser::STRING;
        this->setString(is, next, temp);
        return;
    }
    if (next == '[')
    {
        //! stava segmentation fault
        temp->type = Parser::ARRAY;
        this->setArray(is, next, temp);
        return;
    }

    temp->type = Parser::NUM;
    this->setNum(is, next, temp);
}

void Parser::printCommandInterp(std::istream &is, char &next)
{
    SpaceRemover(is, next);

    if (next == '\"')
    {
        is.get();
        next = is.peek();
        std::string exp;
        getline(is, exp, '\"');
        is.get(); // remove "
        is.get(); // remove ;
        next = is.peek();
        std::cout << exp << '\n';
        return;
    }
    std::string exp;
    getline(is, exp, ';');

    typename ::Parser::Node *tempNode = find(exp);
    if (tempNode)
    {
        if (tempNode->type == Parser::STRING)
        {
            StringValue *tmp = dynamic_cast<StringValue *>(tempNode->value);
            tmp->print();
            std::cout << '\n';

            return;
        }
        if (tempNode->type == Parser::BOOL)
        {
            BoolValue *tmp = dynamic_cast<BoolValue *>(tempNode->value);
            tmp->print();
            std::cout << '\n';

            return;
        }
        if (tempNode->type == Parser::ARRAY)
        {
            ArrayValue *tmp = dynamic_cast<ArrayValue *>(tempNode->value);
            tmp->print();
            std::cout << '\n';
            return;
        }
    }
    exp += ";";
    std::stringstream expression(exp);
    std::stringstream RPexpression(infixToRPN(expression));
    // std::stringstream expression(exp);
    std::cout << RPNeval(RPexpression) << '\n';
}

void Parser::readCommandInterp(std::istream &is, char &next)
{
    SpaceRemover(is, next);
    Parser::Node *temp = new Parser::Node;

    std::string tempKey;
    while (next != ' ' && next != ';')
    {
        tempKey += next;
        is.get();
        next = is.peek();
    }
    temp->key = tempKey;
    
    std::cout << ">";
    std::string exp;
    getline(std::cin, exp);

    exp += ';';

    is.get(); //* mahame ;
    next = is.peek();

    std::stringstream exprestion(exp);

    char newNext = exprestion.peek();  //! povtarqsht se kod na red 214 i 115   da se obedinqt

    SpaceRemover(exprestion,newNext);

    if (newNext == ':')
    {
        temp->type = Parser::BOOL;
        this->setBool(exprestion, newNext, temp);
        return;
    }
    if (newNext == '\"')
    {
        temp->type = Parser::STRING;
        this->setString(exprestion, newNext, temp);
        return;
    }
    if (newNext == '[')
    {
        //! stava segmentation fault
        temp->type = Parser::ARRAY;
        this->setArray(exprestion, newNext, temp);
        return;
    }

    temp->type = Parser::NUM;
    this->setNum(exprestion, newNext, temp);
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

double Parser::RPNeval(std::istream &in)
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
            for (std::size_t i = 0; i < this->arr.size(); i++)
            {
                if (t.keyword == this->arr[i]->key)
                {
                    assert(arr[i]->type == Parser::NUM);
                    t.value = this->arr[i]->value;
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
            int right = s.top();
            s.pop();
            int left = s.top();
            s.pop();
            s.push(fn(t.symbol)(left, right));
        }
        in >> t;
    }

    // std::cout << "size: " <<s.size() << " ";

    assert(s.size() == 1);
    return s.top();
}

typename ::Parser::Node *Parser::find(std::string key)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (key == arr[i]->key)
        {
            return arr[i];
        }
    }
    return nullptr;
}

void Parser::setNum(std::istream &is, char &next, Node *temp)
{
    temp->value = setNumHelper(is, next);
    this->arr.push_back(temp);
}

void Parser::setArray(std::istream &is, char &next, Node *temp)
{
    ArrayValue *arrayVal = dynamic_cast<ArrayValue *>(temp->value);
    temp->value = setArrayHelper(is, next);
    this->arr.push_back(temp);
}

void Parser::setBool(std::istream &is, char &next, Node *temp)
{
    temp->value = setBoolHelper(is, next);
    this->arr.push_back(temp);
}

void Parser::setString(std::istream &is, char &next, Node *temp)
{
    temp->value = setStringHelper(is, next);
    this->arr.push_back(temp);
}

NumValue *Parser::setNumHelper(std::istream &is, char &next)
{
    std::string exp;
    getline(is, exp);
    std::stringstream expression(exp);
    std::string res = infixToRPN(expression);
    std::stringstream RPexpression(res);
    return new NumValue(RPNeval(RPexpression));
}

StringValue *Parser::setStringHelper(std::istream &is, char &next)
{
    is.get();
    std::string exp;
    getline(is, exp, '\"');
    is.get(); // remove "
    is.get(); // remove ;
    next = is.peek();
    return new StringValue(exp);
}

BoolValue *Parser::setBoolHelper(std::istream &is, char &next)
{
    is.get();
    std::string exp;
    getline(is, exp);
    std::stringstream expression(exp);
    std::string res = infixToRPN(expression);
    std::stringstream RPexpression(res);
    return new BoolValue(RPNeval(RPexpression));
}

ArrayValue *Parser::setArrayHelper(std::istream &is, char &next)
{
    is.get();
    next = is.peek();
    ArrayValue *arrayVal = new ArrayValue();
    while (next != ']')
    {
        if (next == '\"')
        {
            is.get();
            std::string exp;
            getline(is, exp, '\"');
            is.get(); // remove "
            // is.get(); // remove ;
            // next = is.peek();
            // std::cout << "next:" << next;
            // std::cout << "exp:" << exp;

            arrayVal->addElement(new StringValue(exp));
            // std::cout << resVal << " ";
            next = is.peek();

            // arrayVal->addElement(setStringHelper(is, next));
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
            BoolValue* resVal = new BoolValue(RPNeval(RPexpression));
            arrayVal->addElement(resVal);
            next = is.peek();
            
        }
        else if (next == '[')
        {
            arrayVal->addElement(setArrayHelper(is, next));
            is.get(); //* skip [
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
            NumValue* resVal = new NumValue(RPNeval(RPexpression));
            arrayVal->addElement(resVal);
            next = is.peek();
        }
        // std::cout << "ispeek:" << is.peek() << " ";
        // is.get();
        // next = is.peek(); //! remove coma ','
        // NumValue* val = setNumHelper(is,next);
    }

    return arrayVal;
}