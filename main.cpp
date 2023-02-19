#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <ctype.h>
#include <sstream>
#include <vector>
#include <unordered_set>
#include "character_set.h"
#include "Lex_Items.h"
using namespace std;

const unsigned int BUFFER_SIZE = 5096;
const string FILE_NAME = "input.txt";

unordered_set<char> MY_SET = VALID_CHARACTER_SET;
vector<Lex_Item> LexicalVector;

/* File IO in part borrowed from GNU coreutils
    Should in theory store
*/

/* static uintmax_t wc(char const *fname)
{
    static const auto BUFFER_SIZE = 16 * 1024;
    int fd = open(fname, O_RDONLY);
    if (fd == -1)
        handle_error("open");

    // Advise the kernel of our access pattern.
    posix_fadvise(fd, 0, 0, 1); // FDADVICE_SEQUENTIAL

    char buf[BUFFER_SIZE + 1];
    uintmax_t lines = 0;

    while (size_t bytes_read = read(fd, buf, BUFFER_SIZE))
    {
        if (bytes_read == (size_t)-1)
            handle_error("read failed");
        if (!bytes_read)
            break;

        for (char *p = buf; (p = (char *)memchr(p, '\n', (buf + bytes_read) - p)); ++p)
            ++lines;
    }

    return lines;
} */

// Returns -1 if error, 0 if user enters M/m, 1 if user enters F/f
int getInputType()
{
    string str;
    cout << "Would you like to manually enter a string or use the provided input.txt file? (M: manual / F: file)" << endl;
    cin >> str;

    if (str.length() != 1)
    {
        cerr << ("Invalid input length detected");
        return -1;
    }
    const char chr = tolower(str[0]);
    switch (chr)
    {
    case 'm':
        return 0;
        break;
    case 'f':
        return 1;
        break;
    default:
        cout << "Invalid input detected";
        return -1;
    }

    // return (strcmp(str.c_str(), "m") != 0) ? (strcmp(str.c_str(), "f") != 0) ? -2 : 1 : 0;
    //((str != "F" || str != "f") ? -1 : 1) : 1;
}
// Returns a string equal to the user input in console
string getManualInput()
{
    string line, input;
    cout << "Type ctrl-D to enter input for lexical analysis" << endl;
    while (cin >> line)
    {
        input += line;
    }
    return input;
}
// Returns a string equal to the contents of input.txt
string getFileInput()
{
    int buffer;
    char c;
    string word, type;
    string line;
    string input;
    // string tokens[];
    ifstream inFile(FILE_NAME);
    if (!inFile.is_open())
        throw invalid_argument("Cant open file.");

    getline(inFile, line);
    // tokenParser(line);
    /* while (getline(inFile, line))
    {
        cout << "Parsing line: " << line << endl;
        tokenParser(line);
    } */

    return line;
}

/* Given the first character of word, return what lexical type it is
Note: If first letter is capital, it could also be a reserved word */

LexType determineWordType(char c)
{
    if (isupper(c))
        return TypeRef;
    if (islower(c))
        return Identifier;
    if (isdigit(c))
        return Number;
    else
        switch (c)
        {
        case '{':
        case '}':
        case '(':
        case ')':
        case ',':
            return RangeSeparator;
        case ':':
            return Assign;
        }
}
int tokenParser(string str)
{
    string word;
    LexType type;
    // stringstream input(str);
    char c;
    Lex_Item item;
    for (int i = 0; i <= str.length(); i++)
    {
        if (i == 0)
        {
            type = determineWordType(str[0]);
        }
        if (isspace(c))
        {
            // reset word

            i = 0;
        }
        else if (is)
    }
    return 0;
}
int getInputCode()
{
    int inType = getInputType();
    while (inType < 0)
    {
        cout << errorHandler(inType) << endl;
        inType = getInputType();
    }
    switch (inType)
    {
    case 0:
        tokenParser(getManualInput());
        return 0;
    case 1:
        tokenParser(getFileInput());
        return 0;
    default:
        throw invalid_argument("Unexpected value of int inType");
    }
}

int Runner()
{
    return 0;
}
int main()
{

    const string input = getInputCode();
    cout << "Read input: " << endl
         << input << endl;
    char lexInputToken;
    vector<Lex_Item> tokenVec;
    return 0;
}