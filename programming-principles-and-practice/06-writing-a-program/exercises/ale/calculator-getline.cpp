/**
 * this is the calculator the co-learning group produced during the exercises hour
 */
#include <iostream>
#include <string>
#include <exception>
#include <sstream>
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
        void set(string);
        Token get();
        void put_back(Token t);
    private:
        istringstream calculation;
        bool full = false;
        Token buffer;
};

void Token_stream::set(string calculation) {
    Token_stream::calculation.str(calculation);
}
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
    calculation >> c;
    if (isdigit(c)) {
        t.kind = 'n';
        t.value = c - '0';
    } else if (c == ' ') {
        // TODO: ignore it ?
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
        t.kind = c;
    } else if (c == '\0') {
        t.kind = 'q';
    } else {
        throw std::invalid_argument("just get out");
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

double calculate(string calculation);
double expression();
double term();
double primary();
// Token get_token();

Token_stream ts;

int main() {
    string calculation;
    double result;
    cout << "Please enter an expression (RETURN to quit) :" << endl;
    while (getline(cin, calculation))
    {
        // -3+2
        // -3 + 2
        // 3+(-2*3)
        if (calculation.empty())
            break;
        result = calculate(calculation);
        cout << "result: " << result << endl << "Please enter an expression (RETURN to quit): ";
    }
}

double calculate(string calculation) {
    double result;
    istringstream cs(calculation);
    ts.set(calculation);
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
    cout << "kind" << t.kind << endl;;
    cout << "value" << t.value << endl;
    switch (t.kind) {
        case '(':
            {
                double d = expression();
                t = ts.get();
                if (t.kind != ')') error("')' expected");
                return d;
            }
        case 'n':
            return t.value;
        case 'q':
            return 0;
        default:
            throw std::invalid_argument("primary expected");
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
