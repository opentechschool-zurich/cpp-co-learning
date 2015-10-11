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


void printTokens(vector<Token> tokens) {
    for (int i = 0; i < tokens.size(); ++i) {
        cout << "Token " << i << " kind: " << tokens[i].kind << " value: " << tokens[i].value << '\n';
    }
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

vector<Token> reduceTerms(vector<Token> tokens) {
    cout << "reduceTerms.size():  " << tokens.size() << '\n';
    printTokens(tokens);
    for ( int i=1; i < tokens.size(); ++i ) {
        if ( tokens[i].kind == '*' ) {
            cout << "Found a * on index " << i << '\n';
            if ( tokens[i-1].kind != 'd' || tokens[i+1].kind != 'd' ) {
                error("it is not a multiplication if the token before or after the * is not a number!");
            } else {
                tokens[i-1].value = tokens[i-1].value * tokens[i+1].value;
                tokens.erase(tokens.begin()+i);
                tokens.erase(tokens.begin()+i);
                --i;
            }
        } else if ( tokens[i].kind == '/' ) {
            cout << "Found a / on index " << i << '\n';
            if ( tokens[i-1].kind != 'd' || tokens[i+1].kind != 'd' ) {
                error("it is not a division if the token before or after the / is not a number!");
            } else {
                tokens[i-1].value = tokens[i-1].value / tokens[i+1].value;
                tokens.erase(tokens.begin()+i);
                tokens.erase(tokens.begin()+i);
                --i;
            }
        }
    }
    cout << "reduceTerms.size():  " << tokens.size() << '\n';
    printTokens(tokens);
    return tokens;
}

vector<Token> reduceExpressions(vector<Token> tokens) {
    cout << "reduceExpressions.size():  " << tokens.size() << '\n';
    printTokens(tokens);
    for ( int i=1; i < tokens.size(); ++i ) {
        if ( tokens[i].kind == '+' ) {
            cout << "Found a + on index " << i << '\n';
            if ( tokens[i-1].kind != 'd' || tokens[i+1].kind != 'd' ) {
                error("it is not an addition if the token before or after the + is not a number!");
            } else {
                tokens[i-1].value = tokens[i-1].value + tokens[i+1].value;
                tokens.erase(tokens.begin()+i);
                tokens.erase(tokens.begin()+i);
                --i;
            }
        } else if ( tokens[i].kind == '-' ) {
            cout << "Found a - on index " << i << '\n';
            if ( tokens[i-1].kind != 'd' || tokens[i+1].kind != 'd' ) {
                error("it is not a subtraction if the token before or after the - is not a number!");
            } else {
                tokens[i-1].value = tokens[i-1].value - tokens[i+1].value;
                tokens.erase(tokens.begin()+i);
                tokens.erase(tokens.begin()+i);
                --i;
            }
        }
    }
    cout << "reduceExpressions.size():  " << tokens.size() << '\n';
    printTokens(tokens);
    return tokens;
}

double parseMathExpression(string expression) {
    vector<Token> tokens = parseExpression(expression);
    vector<Token> termReducedTokens = reduceTerms(tokens);
    vector<Token> expressionReducedTokens = reduceExpressions(tokens);
    return expressionReducedTokens[0].value;
}

void printTokenisation(string expression) {
    vector<Token> tokens = parseExpression(expression);
    cout << "-------------\n" << expression << " parses as:\n";
    for (int i = 0; i < tokens.size(); ++i) {
        cout << "Token " << i << " kind: " << tokens[i].kind << " value: " << tokens[i].value << '\n';
    }
}


int main(int argc, char** argv) {
    string exp2 = "2+4+6";
    printTokenisation(exp2);
    string exp3 = "2+(4+6)";
    printTokenisation(exp3);
    string exp4 = "2*(4+6)";
    printTokenisation(exp4);
    string exp5 = "26/(8-4)";
    printTokenisation(exp5);
    string exp6 = "(2*13)/(8-4)";
    printTokenisation(exp6);
    return 0;
}

