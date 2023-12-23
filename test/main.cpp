#define DOCTEST_CONFIG_IMPLEMENT
#include "Interpreter.hpp"
#include "doctest.h"
#include <iostream>
#include <cassert>

// TEST_CASE("class NumValue constructor testing")
// {
//     NumValue temp(4.5);

//     CHECK(temp.getValue() == 4.5);
// }

// TEST_CASE("class ArrayValue addElement testing")
// {
//     ArrayValue arr;
//     NumValue n(5.4);
//     StringValue s("hello");
//     BoolValue b(true);
//     ArrayValue arr1;
//     StringValue s1("world");
//     StringValue s2("of FMI");
//     arr1.addElement(&s1);
//     arr1.addElement(&s2);
//     arr.addElement(&n);
//     arr.addElement(&s);
//     arr.addElement(&b);
//     arr.addElement(&arr1);

//     // arr.print();

// }

// TEST_CASE("Test Tokenization")
// {
//     std::vector<std::string> strings = {"(1+2)*3;", 
//                                         "(999+0)-73;", 
//                                         "(   1  +    8  )    /    9   ;"};

//     std::vector<Tokenizer::Token_type> expected = {     Tokenizer::OPEN_BRACK, 
//                                                         Tokenizer::NUMBER,
//                                                         Tokenizer::OPERATOR,
//                                                         Tokenizer::NUMBER,
//                                                         Tokenizer::CLOSE_BRACK,
//                                                         Tokenizer::OPERATOR,
//                                                         Tokenizer::NUMBER,
//                                                         Tokenizer::STOP_SYMBOL};

//     Tokenizer::Token token;

//     for (std::string s : strings)
//     {
//         std::stringstream expression(s);
//         int count = 0;
//         while (count < expected.size())
//         {
//             expression >> token;
//             CHECK(token.type == expected[count]);
//             ++count;
//         }
//     }    

//     std::vector<std::string> st = {"(hello+world)-ivan;"};

//     std::vector<Tokenizer::Token_type> expected1 = { Tokenizer::OPEN_BRACK,
//                                                     Tokenizer::STR,
//                                                     Tokenizer::OPERATOR,                                                
//                                                     Tokenizer::STR,
//                                                     Tokenizer::CLOSE_BRACK,
//                                                     Tokenizer::OPERATOR,
//                                                     Tokenizer::STR,
//                                                     Tokenizer::STOP_SYMBOL
//                                                     };

//     Tokenizer::Token token1;
//     for (std::string s : st)
//     {
//         std::stringstream expression(s);
//         int count = 0;
//         while (count < expected1.size())
//         {
//             expression >> token1;
//             CHECK(token1.type == expected1[count]);
//             ++count;
//         }
//     }    

// }

// TEST_CASE("infix to rpn")
// {
//     std::vector<std::pair<std::string,std::string>> expressions = 
//                                                           {{"8+1;","8 1 + ;"},
//                                                            {"101-1-1;","101 1 - 1 - ;"},
//                                                            {"(1+2)*(3+4);","1 2 + 3 4 + * ;"},
//                                                            {"(1+1)*(2+3)+8;","1 1 + 2 3 + * 8 + ;"},
//                                                            {"( a + b ) * c;","a b + c * ;"},
//                                                            {"(ivan+pavel)/petur;", "ivan pavel + petur / ;"}};    

//     for(std::pair<std::string,std::string> p : expressions) 
//     {
//         std::stringstream e (p.first);
//         CHECK(infixToRPN(e) == p.second);
//     }
// }

// TEST_CASE("Test RPN Evaluation")
// {
//     std::vector<std::pair<std::string,double>> expressions = {{"8 1 + ;",9},
//                                                            {"101 1 - 1 - ;",99},
//                                                            {"1 2 + 3 4 + * ;",21},
//                                                            {"1 1 + 2 3 + * 8 + ;",18},
//                                                            {"21 2 * 41 - ;",1},
//                                                            {"36 3 / ;",12},
//                                                            {"1 6 * 6 /;",1}};    

//     Parser a;                                              
//     for(std::pair<std::string,int> p : expressions)
//     {
//         std::stringstream e (p.first);
//         CHECK(RPNeval(e,a) == p.second);
        
//     }
// }

// TEST_CASE("Test Tree Evaluation")
// {
//     Parser par;

//     std::vector<std::pair<std::string,int>> expressions = {{"((1+2)*3)",9},
//                                                            {"99",99},
//                                                            {"(3*(1+2))",9},
//                                                            {"(((1+1)*(2+3))+8)",18},
//                                                            {"if (1+2) then 3 else 4",3}};    
//     for(std::pair<std::string,int> p : expressions)
//     {
//         std::stringstream e (p.first);

//         Expression* t = par.parseExpression(e);

//         CHECK(t->eval() == p.second);
//     }

// }

int main(int argc, char **argv)
{
    // doctest::Context().run();
    return 0;
}