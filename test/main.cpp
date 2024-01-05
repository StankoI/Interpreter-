#define DOCTEST_CONFIG_IMPLEMENT
#include "Interpreter.hpp"
#include "doctest.h"
#include <iostream>
#include <cassert>
#include <sstream>

TEST_CASE("class NumValue constructor testing")
{
    NumValue temp(4.5);

    CHECK(temp.getValue() == 4.5);
}

TEST_CASE("class BoolValue constructor testing")
{
    BoolValue temp(1);

    CHECK(temp.getValue() == true);
}

TEST_CASE("class StringValue constructor testing")
{
    StringValue temp("HELLO WORLD");

    CHECK(temp.getValue() == "HELLO WORLD");
}

TEST_CASE("class ArrayValue addElement testing")
{
    ArrayValue arr; 
    NumValue n(5.4);
    StringValue s("hello");
    BoolValue b(true);
    arr.addElement(&n);
    arr.addElement(&s);
    arr.addElement(&b);

    CHECK(dynamic_cast <NumValue*>(arr.getElementByIndex(0))->getValue() == n.getValue());
    CHECK(dynamic_cast <StringValue*>(arr.getElementByIndex(1))->getValue() == s.getValue());
    CHECK(dynamic_cast <BoolValue*>(arr.getElementByIndex(2))->getValue() == b.getValue());
}

TEST_CASE("Test Tokenization")
{
    std::vector<std::string> strings = {"(1+2)*3;", 
                                        "(999+0)-73;", 
                                        "(   1  +    8  )    /    9   ;"};

    std::vector<Tokenizer::Token_type> expected = {     Tokenizer::OPEN_BRACK, 
                                                        Tokenizer::NUMBER,
                                                        Tokenizer::OPERATOR,
                                                        Tokenizer::NUMBER,
                                                        Tokenizer::CLOSE_BRACK,
                                                        Tokenizer::OPERATOR,
                                                        Tokenizer::NUMBER,
                                                        Tokenizer::STOP_SYMBOL};

    Tokenizer::Token token;

    for (std::string s : strings)
    {
        std::stringstream expression(s);
        int count = 0;
        while (count < expected.size())
        {
            expression >> token;
            CHECK(token.type == expected[count]);
            ++count;
        }
    }    

    std::vector<std::string> st = {"(hello+world)-ivan;"};

    std::vector<Tokenizer::Token_type> expected1 = { Tokenizer::OPEN_BRACK,
                                                    Tokenizer::STR,
                                                    Tokenizer::OPERATOR,                                                
                                                    Tokenizer::STR,
                                                    Tokenizer::CLOSE_BRACK,
                                                    Tokenizer::OPERATOR,
                                                    Tokenizer::STR,
                                                    Tokenizer::STOP_SYMBOL
                                                    };

    Tokenizer::Token token1;
    for (std::string s : st)
    {
        std::stringstream expression(s);
        int count = 0;
        while (count < expected1.size())
        {
            expression >> token1;
            CHECK(token1.type == expected1[count]);
            ++count;
        }
    }    


    std::vector<std::string> strings1 = {"(69 + 420) * f[a];", 
                                         "(999-63)-c[a];", 
                                         "(   115  *    8  )    /    f[b]   ;"};

    std::vector<Tokenizer::Token_type> expected2 = {    Tokenizer::OPEN_BRACK, 
                                                        Tokenizer::NUMBER,
                                                        Tokenizer::OPERATOR,
                                                        Tokenizer::NUMBER,
                                                        Tokenizer::CLOSE_BRACK,
                                                        Tokenizer::OPERATOR,
                                                        Tokenizer::FUNC,
                                                        Tokenizer::STOP_SYMBOL};

    Tokenizer::Token token3;

    for (std::string s : strings1)
    {
        std::stringstream expression(s);
        int count = 0;
        while (count < expected2.size())
        {
            expression >> token3;
            CHECK(token3.type == expected2[count]);
            ++count;
        }
    }
}

TEST_CASE("infix to rpn")
{
    std::vector<std::pair<std::string,std::string>> expressions = 
                                                          {{"8+1;","8 1 + ;"},
                                                           {"101-h[(z+1)]-1;","101 h[(z+1)] - 1 - ;"},
                                                           {"(1+2)*(3+4);","1 2 + 3 4 + * ;"},
                                                           {"(1+1)*(2+3)+8;","1 1 + 2 3 + * 8 + ;"},
                                                           {"( a + f[x-69] ) * c ;","a f[x-69] + c * ;"},
                                                           {"(ivan+g[y*8])/petur;", "ivan g[y*8] + petur / ;"}};

    for(std::pair<std::string,std::string> p : expressions) 
    {
        std::stringstream e (p.first);
        CHECK(infixToRPN(e) == p.second);
    }
}

TEST_CASE("Test RPN Evaluation")
{
    std::vector<std::pair<std::string,double>> expressions = {{"8 1 + ;",9},
                                                           {"101 1 - 1 - ;",99},
                                                           {"1 2 + 3 4 + * ;",21},
                                                           {"1 1 + 2 3 + * 8 + ;",18},
                                                           {"21 2 * 41 - ;",1},
                                                           {"36 3 / ;",12},
                                                           {"1 6 * 6 / ;",1}};    

    Parser a;                                              
    for(std::pair<std::string,int> p : expressions)
    {
        std::stringstream e (p.first);
        CHECK(RPNeval(e,a) == p.second);
        
    }
}

TEST_CASE("Test Tree Evaluation")
{
    Parser par;
    
    Parser::Node* a = new Parser::Node{"a",new NumValue(2),Parser::NUM};
    Parser::Node* b = new Parser::Node{"b",new NumValue(5),Parser::NUM};
    Parser::Node* c = new Parser::Node{"c",new NumValue(9),Parser::NUM};
    Parser::Node* d = new Parser::Node{"d",new NumValue(1),Parser::NUM};
    Parser::Func* f1 = new Parser::Func{"square","(x*x);","x"};
    par.functions.push_back(f1);
    par.arr.push_back(a);
    par.arr.push_back(b);
    par.arr.push_back(c);
    par.arr.push_back(d);

    std::vector<std::pair<std::string,int>> expressions = {{"((1+2)*3)",9},
                                                           {"99",99},
                                                           {"(3*(1+2))",9},
                                                           {"(((1+1)*(2+3))+8)",18},
                                                           {"if (1+2) then 3 else 4",3},
                                                           {"(square[2] + 1);",5},
                                                           {"(a+b);",7},
                                                           {"(c*a);",18},
                                                           {"(b-d);",4}};    
    for(std::pair<std::string,int> p : expressions)
    {
        std::stringstream e (p.first);

        Expression* t = parseExpression(e,par);

        CHECK(t->eval() == p.second);
    }
}

TEST_CASE("TESTING EVAL FUNCTION")
{
    std::function<double(double, double)> opfn;
    
    opfn = fn('+');
    CHECK(opfn(5,5) == 10);
    opfn = fn('*');
    CHECK(opfn(5,5) == 25);
    opfn = fn('-');
    CHECK(opfn(5,5) == 0);
    opfn = fn('/');
    CHECK(opfn(5,5) == 1);
    opfn = fn('^');
    CHECK(opfn(5,2) == 25);
    opfn = fn('=');
    CHECK(opfn(5,5) == 1);
    opfn = fn('=');
    CHECK(opfn(5,4) == 0);
    opfn = fn('|');
    CHECK(opfn(1,0) == 1);
    opfn = fn('|');
    CHECK(opfn(0,0) == 0);
    opfn = fn('&');
    CHECK(opfn(1,0) == 0);
    opfn = fn('&');
    CHECK(opfn(1,1) == 1);
    opfn = fn('%');
    CHECK(opfn(5,4) == 1);
    
}

TEST_CASE("TESTING FINDING FUNCTIONS AND VARIABLES THAT EXIST")
{
    Parser par;
    Parser::Node* a = new Parser::Node{"a",nullptr,Parser::NUM};
    Parser::Node* b = new Parser::Node{"b",nullptr,Parser::NUM};
    Parser::Node* c = new Parser::Node{"c",nullptr,Parser::NUM};
    Parser::Node* d = new Parser::Node{"d",nullptr,Parser::NUM};
    par.arr.push_back(a);
    par.arr.push_back(b);
    par.arr.push_back(c);
    par.arr.push_back(d);

    CHECK(par.find("b") != nullptr);
    CHECK(par.find("e") == nullptr);

    Parser::Func* f1 = new Parser::Func{"f1","x^x","x"};
    Parser::Func* f2 = new Parser::Func{"f2","x^x","x"};

    par.functions.push_back(f1);
    par.functions.push_back(f2);

    CHECK(par.findFunction("f1") != nullptr);
    CHECK(par.findFunction("f3") == nullptr);
}

TEST_CASE("Func command interpretation")
{
    FuncCommand fc;
    Parser par;

    std::string str = "name[par] = (par+par);";
    std::stringstream expr(str);
    char next = expr.peek();

    fc.interpret(expr,next,par);

    Parser::Func* fn = par.findFunction("name");
    CHECK(fn != nullptr);
    CHECK(fn->body == "(par+par);");
    CHECK(fn->varible == "par");
}

TEST_CASE("Set command interpretation")
{
    Parser par;

    std::string setA = "a = 6+9;";
    std::string setB = "b = \"Hello World\";";
    std::string setC = "c = :0;" ;
    std::string setD = "d = [1,2,3,];" ;


    std::stringstream exprA(setA);
    std::stringstream exprB(setB);
    std::stringstream exprC(setC);
    std::stringstream exprD(setD);

    char nextA = exprA.peek();
    char nextB = exprB.peek();
    char nextC = exprC.peek();
    char nextD = exprD.peek();


    SetCommand st;

    st.interpret(exprA,nextA,par);
    st.interpret(exprB,nextB,par);
    st.interpret(exprC,nextC,par);
    st.interpret(exprD,nextD,par);

    Parser::Node* nd1 = par.find("a");
    Parser::Node* nd2 = par.find("b");
    Parser::Node* nd3 = par.find("c");
    Parser::Node* nd4 = par.find("d");

    CHECK(nd1 != nullptr);
    CHECK(nd2 != nullptr);
    CHECK(nd3 != nullptr);
    CHECK(nd4 != nullptr);

    CHECK(nd1->type == Parser::NUM);
    CHECK(nd2->type == Parser::STRING);
    CHECK(nd3->type == Parser::BOOL);
    CHECK(nd4->type == Parser::ARRAY);

}

TEST_CASE("Test Set Existing Node")
{
    Parser par;

    Parser::Node* a = new Parser::Node{"a",new NumValue(5), Parser::NUM};
    Parser::Node* b = new Parser::Node{"b",new BoolValue(0), Parser::BOOL};
    Parser::Node* c = new Parser::Node{"c",new StringValue("hello"), Parser::STRING};

    par.arr.push_back(a);
    par.arr.push_back(b);
    par.arr.push_back(c);

    std::string str1 = "= 8;";
    std::string str2 = "= :1;";
    std::string str3 = "= \"world\";";

    std::stringstream expr1(str1);
    std::stringstream expr2(str2);
    std::stringstream expr3(str3);

    char next1 = expr1.peek();
    char next2 = expr2.peek();
    char next3 = expr3.peek();

    setExistingNode(a,expr1,next1,par);
    setExistingNode(b,expr2,next2,par);
    setExistingNode(c,expr3,next3,par);

    CHECK(dynamic_cast<NumValue*>(a->value)->getValue() == 8);
    CHECK(dynamic_cast<BoolValue*>(b->value)->getValue() == true);
    CHECK(dynamic_cast<StringValue*>(c->value)->getValue() == "world");
}

int main(int argc, char **argv)
{
    doctest::Context().run();
    return 0;
}