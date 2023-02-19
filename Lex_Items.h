#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include <typeinfo>

// Map of all possible lexical token types, and the type they will be converted to
std::unordered_set<std::string> Reserved_Words = RESERVED_WORDS;
std::unordered_map<std::string, std::type_index> Lex_Type_Set = {
    {"ReservedWord", typeid(std::string)},
    {"Range_Separator", typeid(std::string)},
    {"ASSIGN", typeid(std::string)},
    {"LCURLY", typeid(char)},
    {"RCURLY", typeid(char)},
    {"COMMA", typeid(char)},
    {"LPAREN", typeid(char)},
    {"RPAREN", typeid(char)},
    {"TypeRef", typeid(std::string)},
    {"Identifier", typeid(std::string)},
    {"Number", typeid(std::string)},
};

int errorHandler(std::string str)
{
    throw std::runtime_error(str);
}

template <typename TN>
std::string type_name();

// template <class T> Would allow for variable types
typedef struct Node
{
    std::string name;
    bool isFinal = 0;
    struct Node *zeroInput = NULL;
    struct Node *oneInput = NULL;
} State;
class Lex_Item //(string: lexType, string: item)
{
    std::string lexType, lexItem;
    // T item; // item is of whatever type is passed on Lex_Items<type> myItem (lexType, item)
    //  std::type_index itemType;
    //   Lex_Items *assigned; // Do i need a pointer to assignments?
public:
    Lex_Item()
    {
        lexType = "Undefined";
        lexItem = "Undefined";
        // itemType = typeid(void);
    }
    /* Lex_Item(std::string lexType, std::string item)
    {
        this->lexType = lexType;
        this->item = item;
    }
    Lex_Item(std::string lexType, std::string item, std::type_index type)
    {
        if (Lex_Type_Set.count(lexType))
        {
            if (Lex_Type_Set.at(lexType) == type)
            {
                this->lexType = lexType;
                this->item = item;
            }
            else
            {
                throw std::runtime_error("ERROR: IMPROPER TYPE DETECTED IN CLASS Lex_Items.");
            }
        }
        else
        {
            throw std::runtime_error("ERROR: IMPROPER TYPE DETECTED IN CLASS Lex_Items.");
        }
    } */
    int setLexType(std::string str)
    {
        if (Lex_Type_Set.count(str))
        {
            // if there is a key "str" on map Lex_Type_Set
            this->lexType = str;
            return 0;
        }
        else
        {
            std::cout << "ERROR: IMPROPER TYPE DETECTED IN CLASS Lex_Items." << std::endl;
            return -1;
        }
    }

    int setItem(std::string str)
    {
        for (auto &ch : str)
        {
        }
    }
    int setLexItem(std::string type, std::string item)
    {
        if (Lex_Type_Set.count(type))
        {
            // if there is a key "str" on map Lex_Type_Set
            this->lexType = type;
        }
        else
        {
            std::cerr << "Error: Unexpected Lex Type provided while setting Lexical Item";
            return -1;
        }
        return 0;
    }
};