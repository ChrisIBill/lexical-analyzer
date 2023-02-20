#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include <typeinfo>

// Map of all possible lexical token types, and the type they will be converted to
std::unordered_set<std::string> Reserved_Words = RESERVED_WORDS;

// ReservedWord, Range_Separator, Assign,LCurly, RCurly, Comma, LParen, RParen, TypeRef, Identifier, Number
const std::string LEX_TYPES[] = {
    "Undefined",
    "ReservedWord",
    "RangeSeparator",
    "Assign",
    "TypeRef",
    "Identifier",
    "Number",
    "LCurly",
    "RCurly",
    "Comma",
    "LParen",
    "RParen",
    "Misc",
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
    LCurly,
    RCurly,
    Comma,
    LParen,
    RParen,
    Misc,
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
class Lex_Token //(string: lexType, string: item)
{
    LexType lexType;
    std::string lexItem;

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
            std::cout << "Checking range sep" << std::endl;
            isValid = checkRangeSep(str);
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
            break;
        case LCurly:
        case RCurly:
        case Comma:
        case LParen:
        case RParen:
            isValid = checkParens(str);
            break;
        case Misc:
            isValid = checkMisc(str);
            break;
        }
        std::cout << "isValid?: " << isValid << std::endl;
        if (isValid)
        {
            this->lexItem = str;
            return 0;
        }
        else
        {
            this->lexItem = str;
            this->lexType = Error;
            return -1;
        }
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
    bool checkRangeSep(std::string str)
    {
        if (str == "..")
        {
            return true;
        }
        return false;
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
        if (str.back() == '-')
        {
            return -1;
        }
        for (char &c : str)
        {
            if (!isalnum(c))
            {
                if (c != '-' && c != '.')
                {
                    std::cout << "Failing char: " << c << std::endl;
                    return false;
                }
            }
            else
            {
                prevHyphen = false;
            }
        }
        return true;
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
    bool checkParens(std::string str)
    {
        if (str.length() > 1)
        {
            std::cout << "Error: size of parens shouldnt be greater than 1" << std::endl;
            return false;
        }
        return true;
    }
    bool checkMisc(std::string str)
    {
        const char &c = str[0];
        if (str.size() > 1)
        {
            std::cout << "Error: size of misc shouldnt be greater than 1" << std::endl;
            return false;
        }
        else if (c == '"' || c == '|' || c == '=')
        {
            return true;
        }
        else
            return false;
    }
    void printLexToken()
    {
        std::cout << this->lexItem << "(" << LEX_TYPES[this->lexType] << ")" << std::endl;
    }
};