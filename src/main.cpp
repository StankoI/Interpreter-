#include "Interpreter.hpp"
#include <iostream>
#include <cassert>

int main()
{
    std::ifstream is("test.stuck");
    if (!is.is_open())
    {
        return 1;
    }

    Interpreter a;


    a.readFile(is);

    // todo list : making classes for all setFunc files where i will have set with ':' , '\"' , '[' and this will help with eval
    // todo to change the names of command to commandInterpreter and the following classes 
    // todo unit tests
    
    return 0;
}
