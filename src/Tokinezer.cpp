#include "Tokenizer.hpp"
#include <iostream>
#include <fstream>

void SpaceRemover(std::istream &is, char &next)
{
    while (next == ' ' || next == '\n' || next == '\t')
    {
        is.get();
        next = is.peek();
    }
}

std::istream& operator>>(std::istream& is, Tokenizer::Token& t)
{
    char next = is.peek();
    
    SpaceRemover(is,next);

    switch (next)
    {
    case '(':
        t.type = Tokenizer::OPEN_BRACK;
        t.symbol = next;
        is.get();
        return is;
    case ')':
        t.type = Tokenizer::CLOSE_BRACK;
        t.symbol = next;
        is.get();
        return is;
    case '+':
    case '-':
    case '*':       
    case '/':
    case '>':
    case '<':
    case '=':
    case '^':
    case '&':
    case '|':
    case '%':
        t.type = Tokenizer::OPERATOR;
        t.symbol = next;
        is.get();
        return is;
    case ';':
        t.type = Tokenizer::STOP_SYMBOL;
        t.symbol = next;
        is.get();
        return is;
    }

    if(std::isdigit(next))
    {
        t.type = Tokenizer::NUMBER;
        double temp;
        is >> temp;
        //! ako se chupi nqkude tuk e
        // std::cout << temp << " ";
        t.value = new NumValue(temp);
        return is;
    }

    // Predpolagame che e ime na promenliva
    std::string keyWordTemp;
    while( next != ' ' && next != '(' && next != ')' && next != '+' 
        && next != '-' && next != '/' && next != ';'
        && next != '*' && next != '<' && next != '>'
        && next != '=' && next != '^' && next != '%'
        && next != '|' && next != '&')
    {
        if(next == '[')
        {
            while(next != ']')
            {
                keyWordTemp += next;
                is.get();
                next = is.peek();
            }
        }
        keyWordTemp += next;
        is.get();
        next = is.peek();
    }

    t.keyword = keyWordTemp;

    bool hasSquareBrack = false;   //!tup kod 
    for(int i = 0; keyWordTemp[i] != '\0'; i++)
    {
        if(keyWordTemp[i] == '[')
        {
            hasSquareBrack = true;
        }
    }

    //FUNC type name[par]
    if(hasSquareBrack)
    {
        t.type = Tokenizer::FUNC;
        return is;
    }
    
    //IF
    if(t.keyword == "if")
    {
        t.type = Tokenizer::IF;
        return is;
    }

    //THEN
    if(t.keyword == "then")
    {
        t.type = Tokenizer::THEN;
        return is;
    }

    if(t.keyword == "else")
    {
        t.type = Tokenizer::ELSE;
        return is;
    }

    //default
    t.type = Tokenizer::STR;

    return is;

}

std::ostream& operator<<(std::ostream& os, const Tokenizer::Token& t )
{
    switch(t.type)
    {
        case Tokenizer::NUMBER:{
            NumValue* ktmp = dynamic_cast<NumValue*>(t.value);
            os << ktmp->getValue();    //! ako gurmi moje da e tuk
            break;
        }
        case Tokenizer::OPERATOR:
        case Tokenizer::OPEN_BRACK:
        case Tokenizer::CLOSE_BRACK:
        case Tokenizer::STOP_SYMBOL:
            os << t.symbol;
            break;
        case Tokenizer::STR:
            // std::cout << t.keyword << " ";
            os << t.keyword;
            break;
        default:
            os << t.keyword;
            break;
    }

    return os;
}
std::ifstream& operator>>(std::ifstream& is, Tokenizer::Token& t)
{
    char next = is.peek();
    
    SpaceRemover(is,next);

    switch (next)
    {
    case '(':
        t.type = Tokenizer::OPEN_BRACK;
        t.symbol = next;
        is.get();
        return is;
    case ')':
        t.type = Tokenizer::CLOSE_BRACK;
        t.symbol = next;
        is.get();
        return is;
    case '+':
    case '-':
    case '*':       
    case '/':
    case '>':
    case '<':
    case '=':
    case '^':
    case '|':
    case '&':
    case '%':
        t.type = Tokenizer::OPERATOR;
        t.symbol = next;
        is.get();
        return is;
    case ';':
        t.type = Tokenizer::STOP_SYMBOL;
        t.symbol = next;
        is.get();
        return is;
    }

    if(std::isdigit(next))
    {
        t.type = Tokenizer::NUMBER;
        double temp;
        is >> temp;
        //! ako se chupi nqkude tuk e
        // std::cout << temp << " ";
        t.value = new NumValue(temp);
        return is;
    }

    // Predpolagame che e ime na promenliva
    std::string keyWordTemp;
    while( next != ' ' && next != '(' && next != ')' && next != '+' 
        && next != '-' && next != '/' && next != ';'
        && next != '*' && next != '<' && next != '>'
        && next != '=' && next != '^' && next != '%'
        && next != '|' && next != '&')
    {
        if(next == '[')
        {
            while(next != ']')
            {
                keyWordTemp += next;
                is.get();
                next = is.peek();
            }
        }
        keyWordTemp += next;
        is.get();
        next = is.peek();
    }
    // is >> t.keyword;
    // t.keyword = keyWordTemp;

    t.keyword = keyWordTemp;

    bool hasSquareBrack = false;   //!tup kod 
    for(int i = 0; keyWordTemp[i] != '\0'; i++)
    {
        if(keyWordTemp[i] == '[')
        {
            hasSquareBrack = true;
        }
    }

    //FUNC type name[par]
    if(hasSquareBrack)
    {
        t.type = Tokenizer::FUNC;
        return is;
    }
    
    //IF
    if(t.keyword == "if")
    {
        t.type = Tokenizer::IF;
        return is;
    }

    //THEN
    if(t.keyword == "then")
    {
        t.type = Tokenizer::THEN;
        return is;
    }

    if(t.keyword == "else")
    {
        t.type = Tokenizer::ELSE;
        return is;
    }

    t.type = Tokenizer::STR;

    return is;
}

Tokenizer::Tokenizer(std::istream &_in):in(_in), peeked(nullptr){} 

typename Tokenizer::Token Tokenizer::getNextToken()
{

    typename Tokenizer::Token result;

    if (peeked != nullptr)
    {
        result = *peeked;
        delete peeked;
        peeked = nullptr;
    } else 
    {
        in >> result;
    }

    return result;
}

typename Tokenizer::Token Tokenizer::peekToken()
{
    if(peeked == nullptr)
    {
        peeked = new Token;
        in >> *peeked;
    }
    return *peeked;
}