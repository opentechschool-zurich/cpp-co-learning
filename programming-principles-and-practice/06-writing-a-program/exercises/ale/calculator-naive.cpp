/**
 * do a calculation
 * - a value can be an integer or a double,
 * - the allowed operators are sum, substraction, division and multiplication,
 * - gives an error if the calculation is not valid.
 *
 * allowed characters:
 * - 0..9
 * - .
 * - - + / *
 * - " "
 */

#include <iostream>
#include <string>
#include <vector>
// #include "catch.hpp"

#include <exception>

#include <cctype> // for isdigit() and isspace()



using namespace std;

double get_result(string);
double get_result(double lhs, char opr, double rhs);
bool is_opr(char);
int get_operator_priority(char);

int main() {
    /*
    string calculation;
    cout << "type a calculation: " << "\n";
    getline(cin, calculation);
    double result = get_result(calculation);
    cout << "result: " << result << "\n";
    */
    vector<string> calculation = {"3+2"};
    for (auto & item : calculation) {
        cout << item << " = " << get_result(item) << "\n";
    }
    return 1;
}

double get_result(string calculation) {
    double lhs = 0.0;
    double rhs = 0.0;
    char opr = ' '; // operator is  protected word

    constexpr int STATE_NONE = 0;
    constexpr int STATE_ERROR = -1;
    constexpr int STATE_READ_NUMBER = 1;
    constexpr int STATE_READ_SPACE = 2;
    constexpr int STATE_READ_OPERATOR = 3;
    string error = "";
    int state = STATE_NONE;
    string buffer_number = "";
    char buffer_opr = ' ';

    calculation += "=";

    for (char& c : calculation) {
        cout << "c: " << c << "\n";
        if (state == STATE_ERROR || opr == '=') {
            // do nothing
        } else if (isdigit((int) c) || c == '.') {
            cout << "d " << c << "\n";
            if (buffer_number.empty()) {
                buffer_number = c;
            } else if (state == STATE_READ_SPACE) {
                state = STATE_ERROR;
                error = "space inside of numbers";
                continue;
            } else {
                buffer_number += c;
            }
            state = STATE_READ_NUMBER;
        } else if (isspace(c)) {
            cout << "s " << c << "\n";
            state = STATE_READ_SPACE;
        } else if (is_opr(c)) {
            cout << "o " << c << "\n";
            if (buffer_opr != ' ' || state == STATE_READ_OPERATOR) {
                state = STATE_ERROR;
                error = "multiple operators in a row";
                continue;
            } else if (buffer_number.empty()) {
                state = STATE_ERROR;
                error = "operator does not come after a number";
                continue;
            } else {

                if (opr = ' ') {
                    lhs = stod(buffer_number);
                } if (get_operator_priority(c) > get_operator_priority(opr)) {
                    rhs = get_result(rhs, c, stod(buffer_number));
                } else {
                    lhs = get_result(lhs, opr, rhs);
                    rhs = stod(buffer_number);
                }
                opr = c;
                buffer_number = "";
                state = STATE_READ_OPERATOR;
            }
        } else {
            state = STATE_ERROR;
            error = "unknown char";
        }
    }
    cout << "state:" << state << "\n";

    if (state == STATE_ERROR) {
        cout << "error: " << error << "\n";
        return 0;
    } else {
        return lhs;
    }
}

double get_result(double lhs, char opr, double rhs) {
    switch (opr) {
        case '+':
            cout << "get_result: " << lhs << " + " << rhs << "\n";
            return lhs + rhs;
        case '-':
            return lhs - rhs;
        case '*':
            return lhs * rhs;
        case '/':
            // TODO: throw exception if rhs == 0
            return lhs / rhs;
    }
}

bool is_opr(char opr) {
    return (opr == '+' || opr == '-' || opr == '*' || opr == '/' || opr == '=');
}

int get_operator_priority(char opr) {
    switch (opr) {
        case '+':
        case '-':
        case '=':
            return 0;
        case '*':
        case '/':
            return 1;
    }
}
