#include "Interpreter.hpp"
#include <iostream>
#include <cassert>

int main()
{
    // std::vector<std::pair<std::string,std::string>> expressions = 
    //                                                       {{"8+1;","8 1 + ;"},
    //                                                        {"101-1-1;","101 1 - 1 - ;"},
    //                                                        {"(1+2)*(3+4);","1 2 + 3 4 + * ;"},
    //                                                        {"(1+1)*(2+3)+8;","1 1 + 2 3 + * 8 + ;"},
    //                                                        {"( a + b ) * c ;","a b + c * ;"},
    //                                                        {"(ivan+paven)/petur;", "ivan pavel + petur / ;"}};

    // for(std::pair<std::string,std::string> p : expressions) 
    // {
    //     std::stringstream e (p.first);
    //     std::cout << infixToRPN(e) << " ";
    // }

    //!
    // std::ifstream is("test.stuck");
    // if (!is.is_open())
    // {
    //     return 1;
    // }

    // Parser a;

    // try
    // {
    //     a.readFromFile(is);
    // } catch (...)
    // {
    //     std::cout << __PRETTY_FUNCTION__ << std::endl;
    // }
    //!

    std::ifstream is("test.stuck");
    if (!is.is_open())
    {
        return 1;
    }

    Interpreter a;

    a.readFile(is);



    // std::cout << std::pow(4, 0.5);

    // BaseValue* h = new NumValue(5);
    // NumValue* hprime = dynamic_cast<NumValue*>(h);
    // hprime->getValue(); 

    // Parser::Node k;

    //k.key = a;
    //k.type = NUM;
    //
    //if(k.type == NUM)
    //{
    //    NumValue* ktmp = dynamic_cast<NumValue*>(k.value);
    //    ktmp->getValue();
    //!!
    // std::string exp = " if (1+2) then 3 else 4";
    // // getline(is, exp);
    // std::stringstream expression(exp);

    // char next = expression.peek();
    // std::string neshto;
    // while(next != ' ' && next != '(')
    // {
    //     neshto+=next;
    //     expression.get();
    //     next = expression.peek();
    // }
    // std::cout << neshto << " ";
    // // expression.get();

    // expression.seekg(0);

    // exp = "";

    // getline(expression, exp);
    // std::cout << exp;
    //!!


    // doctest::Context().run();
    // todo list : making classes for all setFunc files where i will have set with ':' , '\"' , '[' and this will help with eval
    // todo to change the names of command to commandInterpreter and the following classes 
    // todo unit tests
    
    return 0;
}
