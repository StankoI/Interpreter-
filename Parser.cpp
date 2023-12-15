#include "Parser.hpp"
#include <sstream>
#include <stack>
#include <cassert>
#include <functional>

Parser::Parser()
{
    this->arr.push_back(new Node{"AZIS",new NumValue(69),Parser::NUM});
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
                this->readCommandInterp(is, next);
            }
        }
    }
}

void Parser::setCommandInterp(std::istream &is, char &next)
{
    SpaceRemover(is, next);
    Node *temp = new Node;

    std::string tempKey;
    while (next != ' ' && next != '=')
    {
        tempKey += next;
        is.get();
        next = is.peek();
    }

    //! проверка за специални думи които не могат да бъдат използвани за имана на променливи
    if (tempKey == "if" || tempKey == "else" || tempKey == "then" || tempKey == "AZIS")
    {
        throw "this words are SPECIAL";
    }

    Node* existingNode = this->find(tempKey); //!dobavena proverka ako veche exist node s tova ime
    if(existingNode != nullptr)
    {
        this->setExistingNode(existingNode,is,next);
        return;
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
        //! chupi se v setArray
        // std::cout << "newNext:" << next << " ";
        return;
    }
    // if(next == '-')   //!dobavqne na proverka za otricatelni chisla
    // {

    //     temp->type = Parser::NUM;

    //     return;
    // }

    temp->type = Parser::NUM;
    this->setNum(is, next, temp);
    return;
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
    Node *temp = new Node;

    std::string tempKey;
    while (next != ' ' && next != ';')
    {
        tempKey += next;
        is.get();
        next = is.peek();
    }

    if (tempKey == "if" || tempKey == "else" || tempKey == "then" || tempKey == "AZIS")
    {
        throw "this words are SPECIAL";
    }

    Node* existingNode = this->find(tempKey); //!dobavena proverka ako veche exist node s tova ime
    if(existingNode != nullptr)
    {
        this->setExistingNode(existingNode,is,next);
        return;
    }


    temp->key = tempKey;

    std::cout << ">";
    std::string exp;
    getline(std::cin, exp);

    exp += ';';

    is.get(); //* mahame ;
    next = is.peek();

    std::stringstream exprestion(exp);

    char newNext = exprestion.peek(); //! povtarqsht se kod na red 214 i 115   da se obedinqt

    SpaceRemover(exprestion, newNext);

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
        //! stava segmentation fault - veche ne - mai 

        temp->type = Parser::ARRAY;
        this->setArray(exprestion, newNext, temp);
        return;
    }
    // if(newNext == '-')   //!dobavqne na proverka za otricatelni chisla
    // {
    //     std::string fixer;
    //     exprestion >> fixer;
    //     fixer = "0" + fixer;
    //     // std::cout << fixer;
    //     std::stringstream fixedExprestion(fixer);
    //     temp->type = Parser::NUM;
    //     newNext = fixedExprestion.peek();
    //     this->setNum(fixedExprestion, newNext, temp);
    //     return;
    // }

    temp->type = Parser::NUM;
    this->setNum(exprestion, newNext, temp);
    return;
}

void Parser::setExistingNode(Node *existingNode, std::istream &is, char &next)
{
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
        // temp->type = Parser::BOOL;
        if(existingNode->type != Parser::BOOL)
        {
            throw "trying to set different types value";
        }
        else
        {
            delete existingNode->value;
            existingNode->value = this->setBoolHelper(is,next);
        }
        // this->setBool(is, next, temp);
        return;
    }
    if (next == '\"')
    {
        if(existingNode->type != Parser::STRING)
        {
            throw "trying to set different types value";
        }
        else
        {
            delete existingNode->value;
            existingNode->value = this->setStringHelper(is,next);
        }
        // temp->type = Parser::STRING;
        // this->setString(is, next, temp);
        return;
    }
    if (next == '[')
    {
        //! stava segmentation fault
        if(existingNode->type != Parser::ARRAY)
        {
            throw "trying to set different types value";
        }
        else
        {
            delete existingNode->value;
            existingNode->value = this->setArrayHelper(is,next);
        }
        // temp->type = Parser::ARRAY;
        // this->setArray(is, next, temp);
        //! chupi se v setArray
        // std::cout << "newNext:" << next << " ";
        return;
    }
    // if(next == '-')   //!dobavqne na proverka za otricatelni chisla
    // {

    //     temp->type = Parser::NUM;

    //     return;
    // }
    if(existingNode->type != Parser::NUM)
    {
        throw "trying to set different types value";
    }
    else
    {
        delete existingNode->value;
        existingNode->value = this->setNumHelper(is,next);
    }
    // temp->type = Parser::NUM;
    // this->setNum(is, next, temp);
    return;
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
            double right = s.top();
            s.pop();
            double left = s.top();
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

void Parser::setArray(std::istream &is, char &next, Node *temp) //!!!dobavih & na temp
{
    // std::cout << "newNext:";
    // delete temp->value;
    temp->value = nullptr; //! tova opravq neshtata
    ArrayValue *arrayVal = dynamic_cast<ArrayValue *>(temp->value);
    //! TUK SE CHUPI
    // std::cout << "tuk";
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
    if (exp[0] == '-') //! za rabota sus otricatelni chisla
    {
        exp = "0" + exp;
    }
    std::stringstream expression(exp);
    //! трябва да вкарам по някакъв начин оценка на израз с евентуално if else
    //!
    char newNext = expression.peek();

    std::string firstWord;

    SpaceRemover(expression, newNext);

    if (newNext == '(')
    {
        Expression *t = parseExpression(expression);
        // t->eval();
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
        Expression *t = parseExpression(expression);
        // t->eval();
        return new NumValue(t->eval());
    }

    //! ako se scupi nqkude tuk e problema

    expression.seekg(0);

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
            // std::cout << resVal << " ";
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
            BoolValue *resVal = new BoolValue(RPNeval(RPexpression));
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
            NumValue *resVal = new NumValue(RPNeval(RPexpression));
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

// EXPRESSIONS

Expression *Parser::parseConst(Tokenizer &tokens)
{
    assert(tokens.peekToken().type == Tokenizer::NUMBER || tokens.peekToken().type == Tokenizer::STR);
    //! adding work with nodes
    if (tokens.peekToken().type == Tokenizer::STR)
    {
        // for (int i = 0; i < this->arr.size(); i++)
        // {
        Node *element = this->find(tokens.peekToken().keyword);
        if (!element)
        {
            throw "element does't exist";
        }

        // if (tokens.peekToken().keyword == element->key)
        // {

        // this->find(tokens.peekToken().keyword);

        // assert(arr[i]->type == Parser::NUM);
        if (element->type == NUM)
        {
            NumValue *tmp = dynamic_cast<NumValue *>(element->value);
            tokens.getNextToken(); //! i think this will solve the problem
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
        // }
        // }
    }

    NumValue *tmp = dynamic_cast<NumValue *>(tokens.getNextToken().value);

    return new ExprConst(tmp->getValue());
}

Expression *Parser::parseParExpression(Tokenizer &tokens)
{
    //(<left subexpr> <ope> <right subex>)

    assert(tokens.getNextToken().type == Tokenizer::OPEN_BRACK);

    //<left subexpr> <ope> <right subex>)
    Expression *left = parseExpression(tokens);

    //<ope> <right subex>)
    assert(tokens.peekToken().type == Tokenizer::OPERATOR);
    char op = tokens.getNextToken().symbol;

    //<right subex>)
    Expression *right = parseExpression(tokens);

    //)
    assert(tokens.getNextToken().type == Tokenizer::CLOSE_BRACK);

    return new ExprArith(op, left, right);
}

Expression *Parser::parseIfExpression(Tokenizer &tokens)
{
    // if <expression> then <expression> else <expression>

    assert(tokens.getNextToken().type == Tokenizer::IF);

    // std::cout << "keyword: " << tokens.peekToken().type;

    Expression *cond = parseExpression(tokens);

    assert(tokens.getNextToken().type == Tokenizer::THEN);

    Expression *iftrue = parseExpression(tokens);

    assert(tokens.getNextToken().type == Tokenizer::ELSE);

    // tokens.getNextToken();
    // if (tokens.peekToken().type == Tokenizer::IF)
    // {
    //! tuk ima problem ako else e nov if
    // }

    Expression *iffalse = parseExpression(tokens);

    // std::cout << "token: " << tokens.peekToken().keyword;

    return new ExprIf(cond, iftrue, iffalse);
}

Expression *Parser::parseExpression(Tokenizer &tokens)
{

    /*
    <expression> ::= <number> |
                     (<expression> <operator> <exprerssion>) |
                     if <expression> then <expression> else <expression>
    <number> ::= {0,..,9}+
    <operator> ::= + | - | * | /
    */
    // std::cout <<

    if (tokens.peekToken().type == Tokenizer::IF)
    {
        return parseIfExpression(tokens);
    }
    if (tokens.peekToken().type == Tokenizer::NUMBER || tokens.peekToken().type == Tokenizer::STR)
    {
        return parseConst(tokens);
    }
    if (tokens.peekToken().type == Tokenizer::OPEN_BRACK)
    {
        return parseParExpression(tokens);
    }

    throw "Syntax error. Unknown expression type";
    return nullptr;
}

Expression *Parser::parseExpression(std::istream &is)
{
    Tokenizer tokens(is);
    return parseExpression(tokens);
}