#include <iostream>
#include <unordered_set>
#define VALID_CHARACTER_SET                                              \
    {                                                                    \
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',                \
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', \
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', \
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', \
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', \
        '\'', '\"', '(', ')', ',', '-', ':', '=', '{', '}', '|'};
#define RESERVED_WORDS                                        \
    {                                                         \
        "TAGS", "BEGIN", "SEQUENCE", "INTEGER", "DATE", "END" \
    }
// ReservedWord, Range_Separator, Assign,LCurly, RCurly, Comma, LParen, RParen, TypeRef, Identifier, Number
enum LexType
{
    ReservedWord,
    RangeSeparator,
    Assign,
    TypeRef,
    Identifier,
    Number,
    Error
};

/* LCurly,
    RCurly,
    Comma,
    LParen,
    RParen, */