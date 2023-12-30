#include "ExprTree.hpp"
#include <set>
#include <vector>
#include <sstream>

class Parser
{
public:
    enum Value_Type{STRING, BOOL, NUM, ARRAY,FUNC};
    struct Node
    {
        std::string key;
        BaseValue* value = nullptr;
        Value_Type type;

        ~Node();
    };

    struct Func  //!Structura za funkcii
    {
        std::string key;
        Value_Type type;
        std::string body;
        //todo VARIABLE 
        std::string varible;

        // Func(const Func& other);
    };

    std::vector<Node*> arr; //!arr need new name 
    std::vector<Func*> functions;

    std::set<std::string> specialWords; 

    Parser();

    Node* find(const std::string& key);
    Func* findFunction(const std::string& key);
    //todo Destructor, operator=, copyconstructor 

    Parser(const Parser& other);

    Parser& operator=(const Parser& other);

    ~Parser();

private:

    void destroy();

    void copy(const Parser& other);

};
