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
// ReservedWord, Range_Separator, Assign,LCurly, RCurly, Comma, LParen, RParen, TypeRef, Identifier, Number
const std::string LEX_TYPES[] = {
    "Undefined",
    "ReservedWord",
    "RangeSeparator",
    "Assign",
    "TypeRef",
    "Identifier",
    "Number",
    "Space",
    "NewLine",
    "Error"};
enum LexType
{
    Undefined,
    ReservedWord,
    RangeSeparator,
    Assign,
    TypeRef,
    Identifier,
    Number,
    Space,
    NewLine,
    Error
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
class Lex_Token //(string: lexType, string: item)
{
    LexType lexType;
    std::string lexItem;
    // T item; // item is of whatever type is passed on Lex_Items<type> myItem (lexType, item)
    //  std::type_index itemType;
    //   Lex_Items *assigned; // Do i need a pointer to assignments?
public:
    Lex_Token()
    {
        lexType = Undefined;
        lexItem = "Undefined";
        // itemType = typeid(void);
    }

    int setLexType(LexType type)
    {
        if (type == Error || Undefined)
        {
            std::cerr << "Error: Error or undefined type in type set";
            this->lexType = type;
            return -1;
        }
        this->lexType = type;
        return 0;
    }

    int setLexItem(std::string str)
    {
        bool isValid = false;
        if (this->lexType == Error || this->lexType == Undefined)
        {
            std::cerr << "Error: cant assign item with this type " << lexType;
            return -1;
        }
        std::cout << "Checking lexical word " << str << " for validity as type " << lexType << std::endl;
        switch (lexType)
        {
        case ReservedWord:
            // Shouldnt need to check
            std::cerr << "Hit case reserved word for some reason in Lex_Items.h setLexItems";
            isValid = true;
            break;
        case RangeSeparator:
            // Shouldnt need to check
            isValid = true;
            break;
        case Assign:
            isValid = checkAssign(str);
            break;
        case TypeRef:
            if (Reserved_Words.count(str))
            {
                std::cout << "Reserved word detected" << std::endl;
                isValid = true;
                this->lexType = ReservedWord;
                break;
            }
        case Identifier:
            isValid = checkTypeRefOrIdentifier(str);
            break;
        case Number:
            isValid = checkNumber(str);
        }
        std::cout << "isValid?: " << isValid << std::endl;
        if (isValid)
        {
            this->lexItem = str;
            return 0;
        }
        else
            return -1;
    }
    bool checkReservedWord(std::string str)
    {
        if (Reserved_Words.count(str))
        {
            this->lexType = ReservedWord;
            return true;
        }
        else
            return false;
    }
    int checkRangeSep(std::string str)
    {
        // Shouldnt need to check range
    }
    bool checkAssign(std::string str)
    {
        if (str == "::=")
        {
            return true;
        }
        return false;
    }
    bool checkTypeRefOrIdentifier(std::string str)
    {
        bool prevHyphen = false;
        // Need to check if correct type has been applied
        if (str.back() == '-')
        {
            return -1;
        }
        for (char &c : str)
        {
            if (!isalnum(c))
            {
                if (c != '-')
                {
                    return false;
                }
                else
                {
                    // Could also just check next char for hyphen here as well
                    prevHyphen = true;
                }
            }
            else
            {
                prevHyphen = false;
            }
        }
        return true;
    }
    bool checkIdentifier(std::string str)
    {
    }
    bool checkNumber(std::string str)
    {
        if (str.size() > 1)
        {
            if (str[0] == '0')
            {
                std::cerr << "Error: Number other than 0 cannot start with 0";
                return false;
            }
        }
        for (char &c : str)
        {
            if (!isdigit(c))
            {
                std::cerr << "Non-numeric character " << c << " detected in Number " << str;
                return false;
            }
        }
        return true;
    }

    void printLexToken()
    {
        std::cout << this->lexItem << "(" << LEX_TYPES[this->lexType] << ")" << std::endl;
    }
};