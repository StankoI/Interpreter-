#pragma once
#include "printCommand.hpp"
#include "setCommand.hpp"
#include "readCommand.hpp"
#include "funcCommand.hpp"
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

/// Клас Interpreter, интерпретира файл с код написан на Stuck. Съдиржа unordered_map с команди които да разпознава и интерпретира
class Interpreter
{
private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands;

public:
    Interpreter();
    void readFile(std::istream& is);
};