#pragma once
#include "command.hpp"

class SetCommand : public Command
{
public:
    void interpret(std::istream& is, char& next, Parser& object);

    // void setNum(std::istream &is, char &next, Parser::Node *temp, Parser& object);

    // void setBool(std::istream &is, char &next, Parser::Node *temp, Parser& object);

    // void setString(std::istream &is, char &next, Parser::Node *temp, Parser& object);

    // void setArray(std::istream &is, char &next, Parser::Node *temp, Parser& object);

    // NumValue* setNumHelper(std::istream &is, char &next,Parser& object);

    // BoolValue* setBoolHelper(std::istream &is, char &next,Parser& object);

    // StringValue* setStringHelper(std::istream &is, char &next,Parser& object);

    // ArrayValue* setArrayHelper(std::istream &is, char &next,Parser& object);

    // void setExistingNode(Parser::Node* existingNode,std::istream &is, char &next, Parser& object);
    // //!
    // Expression* parseExpression(std::istream &is,Parser& object);

    // Expression* parseExpression(Tokenizer &tokens,Parser& object);

    // Expression *parseConst(Tokenizer &tokens, Parser& object);

    // Expression *parseIfExpression(Tokenizer &tokens,Parser& object);

    // Expression *parseParExpression(Tokenizer &tokens,Parser& object);

};