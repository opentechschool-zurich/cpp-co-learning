#include<istream>
#include<sstream>
#include<string>

#include <algorithm>
#include <exception>
#include <vector>

using namespace std;

class PunctStream {

public:
    PunctStream(istream& source)
        :source{source}, caseSensitivity{true} {}
    void setWhiteSpace(const string& whiteSpace) {
        this->whiteSpace = whiteSpace;
    }
    void addWhiteSpace(char c) {
        whiteSpace += c;
    }
    bool isWhiteSpace(char c);
    void setCaseSensitive(bool caseSensitivity) {
        this->caseSensitivity = caseSensitivity;
    }
    bool isCaseSensitive() {
        return caseSensitivity;
    }
    PunctStream& operator>>(string& s);
    operator bool();

private:
    istream& source;
    istringstream buffer;
    bool caseSensitivity;
    string whiteSpace;

};
