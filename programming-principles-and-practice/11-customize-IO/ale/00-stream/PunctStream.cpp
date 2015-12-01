#include "PunctStream.h"
#include<istream>
#include<string>

using namespace std;

bool PunctStream::isWhiteSpace(char ch) {
    for (char w : whiteSpace) {
        if (ch == w) return true;
    }
    return false;
}

PunctStream& PunctStream::operator>>(string& s)
{
    while (!(buffer >> s)) {
        if (buffer.bad() || !source.good()) return *this;
        buffer.clear();
        string line;
        getline(source, line);
        for (char& ch: line) {
            if (isWhiteSpace(ch)) {
                ch = ' ';
            } else if (!caseSensitivity) {
                ch = tolower(ch);
            }
        }
        buffer.str(line);
    }
    return *this;
}

PunctStream::operator bool()
{
    return !(source.fail() || source.bad()) && source.good();
}
