#include "Interpreter.hpp"
#include <sstream>
#include <memory>

Interpreter::Interpreter()
{
    this->commands["set"] = std::make_unique<SetCommand>();
    this->commands["print"] = std::make_unique<PrintCommand>();
    this->commands["read"] = std::make_unique<ReadCommand>();
    this->commands["func"] = std::make_unique<FuncCommand>();
}

void Interpreter::readFile(std::istream& is)
{
    Parser object;
    
    while(is)
    {
        char next = is.peek();

        SpaceRemover(is,next);

        std::string command;
        is >> command;
        next = is.peek();

        auto it = this->commands.find(command);  
        if(it != this->commands.end())
        {
            it->second->interpret(is,next,object);
        }
        else
        {
            std::cout << "this command does not exist\n";
            throw "this command does not exist";
        }
    }
}
