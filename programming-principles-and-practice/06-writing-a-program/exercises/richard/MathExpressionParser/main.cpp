/* 
 * File:   main.cpp
 * Author: Richard Eigenmann
 *
 * Created on October 4, 2015, 9:27 PM
 */

#include <cstdlib>
#include "std_lib_facilities.h"
#include <vector>

using namespace std;

class Token {
public:
    char kind;
    double value;

    Token(char ch)
    : kind(ch), value(0) {
    }

    Token(char ch, double val)
    : kind(ch), value(val) {
    }
};

Token resolveMathTokens(vector<Token> tokens);

void printTokenVector(vector<Token> tokens) {
    cout << "{";
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens[i].kind << "," << tokens[i].value << '|';
    }
    cout << "}\n";
}

vector<Token> parseExpression(string expression) {
    vector<Token> tokens;

    for (size_t startPos = 0; startPos < expression.size(); startPos++) {
        for (size_t testPos = startPos; testPos < expression.size(); testPos++) {
            char c = expression.at(testPos);
            // if we find a math symbol we have a moved to a new token
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')') {
                if (testPos > startPos) {
                    // only extract a left term if we have seen digits before
                    string leftOfSymbol = expression.substr(startPos, testPos - startPos);
                    double value = atof(leftOfSymbol.c_str());
                    tokens.push_back(Token('d', value));
                }
                tokens.push_back(Token(expression.at(testPos)));
                startPos = testPos + 1;
            }
            // if we hit the end of the line that was it
            if (testPos == expression.size() - 1) {
                if (startPos <= testPos) {
                    // only extract a number is there are characters for a number
                    string leftOfSymbol = expression.substr(startPos, expression.size() - startPos);
                    double value = atof(leftOfSymbol.c_str());
                    tokens.push_back(Token('d', value));
                }
                startPos = expression.size(); // ensure we exit outer loop
            }
        }
    }
    return tokens;
}

vector<Token> reduceNegativeNumbers(vector<Token> tokens) {
    if (tokens[0].kind == '-' && tokens.size() > 1 && tokens[1].kind == 'd') {
        tokens[0].kind = 'd';
        tokens[0].value = 0 - tokens[1].value;
        tokens.erase(tokens.begin() + 1);
    }
    return tokens;
}

vector<Token> reduceTerms(vector<Token> tokens) {
    for (int i = 1; i < tokens.size(); ++i) {
        if (tokens[i].kind == '*') {
            if (tokens[i - 1].kind != 'd' || tokens[i + 1].kind != 'd') {
                error("it is not a multiplication if the token before or after the * is not a number!");
            } else {
                tokens[i - 1].value = tokens[i - 1].value * tokens[i + 1].value;
                tokens.erase(tokens.begin() + i);
                tokens.erase(tokens.begin() + i);
                --i;
            }
        } else if (tokens[i].kind == '/') {
            if (tokens[i - 1].kind != 'd' || tokens[i + 1].kind != 'd') {
                error("it is not a division if the token before or after the / is not a number!");
            } else {
                tokens[i - 1].value = tokens[i - 1].value / tokens[i + 1].value;
                tokens.erase(tokens.begin() + i);
                tokens.erase(tokens.begin() + i);
                --i;
            }
        }
    }
    return tokens;
}

vector<Token> reduceExpressions(vector<Token> tokens) {
    for (int i = 1; i < tokens.size(); ++i) {
        if (tokens[i].kind == '+') {
            if (tokens[i - 1].kind != 'd' || tokens[i + 1].kind != 'd') {
                error("it is not an addition if the token before or after the + is not a number!");
            } else {
                tokens[i - 1].value = tokens[i - 1].value + tokens[i + 1].value;
                tokens.erase(tokens.begin() + i);
                tokens.erase(tokens.begin() + i);
                --i;
            }
        } else if (tokens[i].kind == '-') {
            if (tokens[i - 1].kind != 'd' || tokens[i + 1].kind != 'd') {
                error("it is not a subtraction if the token before or after the - is not a number!");
            } else {
                tokens[i - 1].value = tokens[i - 1].value - tokens[i + 1].value;
                tokens.erase(tokens.begin() + i);
                tokens.erase(tokens.begin() + i);
                --i;
            }
        }
    }
    return tokens;
}

void printTokenisation(string expression) {
    vector<Token> tokens = parseExpression(expression);
    cout << "-------------\n" << expression << " parses as:\n";
    printTokenVector(tokens);
}

bool hasBraces(vector<Token> tokens) {
    for (Token token : tokens) {
        if (token.kind == '(') {
            return true;
        }
    }
    return false;
}

vector<Token> resolveBraceExpression(vector<Token> tokens) {
    int lastOpenPosition = -1;
    int firstClosePosition = -1;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].kind == '(') {
            lastOpenPosition = i;
        } else if (tokens[i].kind == ')') {
            firstClosePosition = i;
            break;
        }
    }

    if (lastOpenPosition > -1 && firstClosePosition > -1) {
        vector<Token> slice;
        for (int i = lastOpenPosition + 1; i <= firstClosePosition - 1; i++) {
            slice.push_back(tokens[i]);
        }
        Token resultToken = resolveMathTokens(slice);
        tokens[lastOpenPosition] = resultToken;
        tokens.erase(tokens.begin() + lastOpenPosition + 1, tokens.begin() + firstClosePosition+1);
    }
    return tokens;
}

Token resolveMathTokens(vector<Token> tokens) {
    cout << "resolveMathTokens called with ";
    printTokenVector(tokens);

    tokens = reduceNegativeNumbers(tokens);
    cout << "after reduceNegativeNumbers: ";
    printTokenVector(tokens);

    while (hasBraces(tokens)) {
        cout << "resolvingBraceExpression...\n";
        tokens = resolveBraceExpression(tokens);
        cout << "after resolveBraceExpression: ";
        printTokenVector(tokens);
    }
    tokens = reduceTerms(tokens);
    cout << "after reduceTerms: ";
    printTokenVector(tokens);
    tokens = reduceExpressions(tokens);
    cout << "after reduceExpressions: ";
    printTokenVector(tokens);
    return tokens[0];
}

double parseMathExpression(string expression) {
    vector<Token> tokens = parseExpression(expression);
    Token token = resolveMathTokens(tokens);
    return token.value;
}

int main(int argc, char** argv) {
    string expression;
    cout << "Type a math expression like 2*(6-2)/2 or q to quit\n";
    while (getline(cin, expression)) {
        if (expression == "q") {
            break;
        }
        cout << parseMathExpression(expression) << '\n';
    }
    //    string exp2 = "2+4+6";
    //    printTokenisation(exp2);
    //    string exp3 = "2+(4+6)";
    //    printTokenisation(exp3);
    //    string exp4 = "2*(4+6)";
    //    printTokenisation(exp4);
    //    string exp5 = "26/(8-4)";
    //    printTokenisation(exp5);
    //    string exp6 = "(2*13)/(8-4)";
    //    printTokenisation(exp6);
    return 0;
}

