/**
 * this is a calculator that:
 * - uses getline() to read a full line at a time
 * - uses istringstream to get the same behavior as cin on a full string
 * - directly uses exceptions
 * - uses catch for unit testing
 * - parses options
 */
#include <iostream>
#include <string>
#include <exception>
#include <sstream>
#include <vector>
#include "optionparser.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

using namespace std;

void error(string message) {
    cout << message << "\n";
}

enum  optionIndex {
    UNKNOWN,
    HELP,
    TEST
 };

const option::Descriptor usage[] =
{
    {UNKNOWN, 0,"" , "",option::Arg::None, "USAGE: alculator [options]\n\n"
        "Options:" },
    {HELP, 0,"h", "help",option::Arg::None, "  --help, -h  \tPrint usage and exit." },
    {TEST, 0,"", "test",option::Arg::None, "  --test       \tRun the tests." },
    {UNKNOWN, 0, "", "",option::Arg::None, "\nExamples:\n"
        "  calculator --test \n"
        "  calculator\n" },
    {0,0,0,0,0,0}
};

class Token {
    public:
        char kind;
        double value;
};

class Token_stream {
    public:
        void set(string line);
        Token get();
        void put_back(Token t);
    private:
        istringstream calculation;
        bool full = false;
        Token buffer;
};

/*
 * build stream from string
 */
void Token_stream::set(string line) { 
    full = false;  
    calculation.clear();
    calculation.str(line);  
}

/**
 * for now only single digit numbers are supported
 */
Token Token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }

    // debugging current string
    cout << "-->" << calculation.str() << endl;

    char c;
    Token t;

    if (calculation.eof()) {
        t.kind = ' ';
        t.value = 0;
        return t;
    }
 
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

int main(int argc, char* argv[]) {

    argc-=(argc>0); argv+=(argc>0); // skip program name argv[0] if present
    option::Stats  stats(usage, argc, argv);
    std::vector<option::Option> options(stats.options_max);
    std::vector<option::Option> buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

    if (parse.error())
        return 1;

    if (options[HELP]/* || argc == 0*/) {
        option::printUsage(std::cout, usage);
        return 0;
    }
    if (options[TEST]) {
        int result = Catch::Session().run( argc, argv );
        return result;
    }


    for (option::Option* opt = options[UNKNOWN]; opt; opt = opt->next()) {
        std::cout << "Unknown option: " << opt->name << "\n";
    }


    string calculation;
    double result;
    cout << "Please enter an expression (RETURN to quit) :" << endl;
    while (getline(cin, calculation))
   {
        if (calculation.empty())
            break;
        result = calculate(calculation);
        cout << "result: " << result << endl << "Please enter an expression (RETURN to quit): ";
    }
}

double calculate(string calculation) {

    double result = 0.0;

    ts.set(calculation);
    result = expression();
    return result;
}

double expression()
{
    double left = term();
    Token t = ts.get();
    switch (t.kind) {
        case ' ':
           return left;
        break;
        case '+':
            return left + term();
        break;
        case '-':
            return left + term();
        break;
        default:
            ts.put_back(t);
            return left;
    }
}

double term()
{
    double left = primary();
     return left;
}

double primary()
{
    double result = 0.0;
    Token t = ts.get();
    cout << t.kind << " / " << t.value << endl;
    result = t.value;

    return result;
}

/*

double calculate(string calculation) {
    double result;
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
*/

TEST_CASE( "r", "[digit]" ) {
    REQUIRE( calculate("4") == 4 );
    REQUIRE( calculate("6") == 6 );
    REQUIRE( calculate("4+2") == 6 );
    // REQUIRE( calculate("4*2") == 8 );
        // -3+2
        // -3 + 2
        // 3+(-2*3)
}
