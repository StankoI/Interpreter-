#include "ExprTree.hpp"
#include <set>
#include <vector>

class Parser
{
    public:
    enum Value_Type{STRING, BOOL, NUM, ARRAY,FUNC};
    struct Node
    {
        std::string key;
        BaseValue* value = nullptr;
        Value_Type type;
    };

    struct Func : public Node  //!Structura za funkcii
    {
        std::vector<Node*> variables;
        Expression* exprTree;
    };

    std::vector<Node*> arr;

    std::set<std::string> specialWords; 

    Parser();

    Node* find(std::string key);

    //todo Destructor, operator=, copyconstructor 
};
