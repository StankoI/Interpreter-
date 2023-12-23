#include "commandInterpreter.hpp"
#include <sstream>

CommandInterpreter::CommandInterpreter()
{
    SetCommand* SET = new SetCommand;
    PrintCommand* PRINT = new PrintCommand;
    ReadCommand* READ = new ReadCommand;
    this->commands["set"] = SET;
    this->commands["print"] = PRINT;
    this->commands["read"] = READ;
    //! maybe needs a destructor 
}

void CommandInterpreter::addCommand(std::string key, Command* value)
{
    this->commands[key] = value;
}

void CommandInterpreter::readFile(std::istream& is)
{
    Parser object;
    
    while(is)
    {
        char next = is.peek();

        SpaceRemover(is,next);

        std::string command;
        is >> command;
        next = is.peek();

        auto it = this->commands.find(command);  //! sorry za auto 
        if(it != this->commands.end())
        {
            it->second->interpret(is,next,object);
        }
        else
        {
            std::cout << "this command does not exist\n";
        }
    }
}
