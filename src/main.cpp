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
    
    return 0;
}
