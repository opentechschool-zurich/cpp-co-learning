/**
 * this is the calculator the co-learning group produced during the exercises hour
 */
#include <iostream>
#include <string>
using namespace std;

void error(string message) {
    cout << message << "\n";
}

class Token {
    public:
        char kind;
        double value;
};

class Token_stream {
    public:
        Token get();
        void put_back(Token t);
    private:
        bool full = false;
        Token buffer;
};

/**
 * for now only single digit numbers are supported
 */
Token Token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }
    char c;
    Token t;
    cin >> c;
    if (isdigit(c)) {
        t.kind = 'n';
        t.value = c - '0';
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
        t.kind = c;
    } else {
        // TODO: throw an exception
    }
    return t;

}

void Token_stream::put_back(Token t) {
    if (full) {
        // TODO: throw an error
        error("filling a full buffer");
    }
    full = true;
    buffer = t;
}

double calculate();
double expression();
double term();
double primary();
// Token get_token();

Token_stream ts;

int main() {
    string calculation;
    double result;
    cout << "Please enter an expression" << "\n";
    while (cin) {
        result = calculate();
        cout << "= " << result << "\n";
        /*
        Token t = get_token();
        cout << t.kind << "\n";
        if (t.kind == 'n') {
            cout << "v: " << t.value << "\n";
        }
        */
    }
    // double result = calculate();
    cout << "= " << result << "\n";
}

double calculate() {
    double result;
    result = expression();
    return result;
}

double expression()
{
    double left = term(); // read and evaluate a Term
    Token t = ts.get(); // get the next token
    while (true) {
        switch (t.kind) {
            case '+':
                left += term(); // evaluate Term and add
                t = ts.get();
                break;
            case '-':
                left -= term(); // evaluate Term and subtract
                t = ts.get();
                break;
            default:
                return left; // finally: no more + or –; return the answer
        }
        cout << "expression::left :" << left << "\n";
    }
}

double term()
{
    double left = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
                { double d = primary();
                    if (d == 0) error("divide by zero");
                    left /= d;
                    t = ts.get();
                    break;
                }
            default:
                ts.put_back(t);
                return left;
        }
    }
}

double primary()
{
    Token t = ts.get();
    switch (t.kind) {
        case '(':
            { double d = expression();
                t = ts.get();
                if (t.kind != ')') error("')' expected");
                return d;
            }
        case 'n':
            return t.value;
        default:
            error("primary expected");
    }
}

/**
 * for now only single digit numbers are supported
 */
/*
Token get_token() {
    Token t;
    char c;
    cin >> c;
    if (isdigit(c)) {
        t.kind = 'n';
        t.value = c - '0';
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
        t.kind = c;
    } else {
        // TODO: throw an exception
    }
    return t;
}
*/
