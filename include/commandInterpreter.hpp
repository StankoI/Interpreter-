#pragma once
#include "printCommand.hpp"
#include "setCommand.hpp"
#include "readCommand.hpp"
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>

class CommandInterpreter
{
private:
    std::unordered_map<std::string, Command *> commands;

public:

    CommandInterpreter();

    void addCommand(std::string key, Command* value);

    void readFile(std::istream& is);

};