#include "ExprTree.hpp"
#include <set>
#include <vector>
#include <sstream>

/// Клас Parser съдуржа вектор с всички променливи дефинирани в езика, вектор със всички функции в езика и set с всички специални думи в езика които не могат да бъдат използвани за име на променлива
class Parser
{
public:
    enum Value_Type{STRING, BOOL, NUM, ARRAY};
    /// Структура за променливите
    struct Node
    {
        std::string key;
        BaseValue* value = nullptr;
        Value_Type type;

        ~Node();
    };
    /// Структура за функциите в езика
    struct Func 
    {
        std::string key;
        // Value_Type type;
        std::string body;
        std::string varible;
    };

    std::vector<Node*> arr;
    std::vector<Func*> functions;
    std::set<std::string> specialWords; 

    Parser();

    Node* find(const std::string& key);
    Func* findFunction(const std::string& key); 

    Parser(const Parser& other);

    Parser& operator=(const Parser& other);

    ~Parser();

private:

    void destroy();

    void copy(const Parser& other);

};
