#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_set>
#include "Lex_Items.h"
#define VALID_CHARACTER_SET                                                  \
    {                                                                        \
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',                    \
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', \
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', \
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', \
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', \
            '\'', '\"', '(', ')', ',', '-', ':', '=', '{', '}', '|'          \
    }
using namespace std;

unordered_set<char> MY_SET = VALID_CHARACTER_SET;

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

// Returns 0 if string input, 1 if file based input and -1 if error
int errorHandler(int err)
{
    switch (err)
    {
    case -1:
        cout << "Error: input length is zero" << endl;
        return 0;
    case -2:
        cout << "Error: invalid input detected" << endl;
        return 0;
    default:
        cout << "Unhandled Error" << endl;
        return -1;
    }
}
int getInputType()
{
    string str;
    cout << "Would you like to manually enter a string or use the provided input.txt file? (M: manual / F: file)" << endl;
    cin >> str;

    if (str.length() == 0)
    {
        return -1;
    }
    str[0] = tolower(str[0]);
    return (strcmp(str.c_str(), "m") != 0) ? (strcmp(str.c_str(), "f") != 0) ? -2 : 1 : 0;
    //((str != "F" || str != "f") ? -1 : 1) : 1;
}
// Returns a string equal to the user input in console
string getManualInput()
{
    return "Undefined";
}
// Returns a string equal to the contents of input.txt
string getFileInput()
{
    return "Undefined";
}
int main()
{
    int inType = getInputType();
    while (inType < 0)
    {
        cout << errorHandler(inType) << endl;
        inType = getInputType();
    }
    const string input = inType == 0 ? getManualInput() : getFileInput();

    char lexInputToken;
    vector<Lex_Item> tokenVec;
    return 0;
}