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
    calculation.str(line);  
    calculation.clear();
}

/**
 * for now only single digit numbers are supported
 */
Token Token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }

    // cout << "-->" << calculation.str() << endl;

    char c;
    Token t;

    calculation >> c;

    if (calculation.eof()) {
        t.kind = ' ';
        t.value = 0;
        return t;
    }

    if (isdigit(c)) {
        t.kind = 'n';
        t.value = c - '0';
    } else if (c == ' ') {
        // TODO: ignore it ?
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '.') {
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
        try {
            result = calculate(calculation);
            cout << "result: " << result << endl;
        } catch (exception& e) {
            cout << "error: " << e.what() << endl;
        }
        cout << "Please enter an expression (RETURN to quit): " << endl;;
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
    while (true) {
        switch (t.kind) {
            case ' ':
               return left;
                break;
            case '+':
                left += term();
                t = ts.get();
                break;
            case '-':
                left -= term();
                t = ts.get();
                break;
            default:
                ts.put_back(t);
                return left;
        }
    }
    return left;
}

double term()
{
    double left = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case ' ':
               return left;
                break;
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
                {
                    double value = primary();
                    if (value == 0.0) {
                        throw overflow_error("divide by zero exception");
                    }
                    left /= value;
                    t = ts.get();
                }
                break;
            default:
                ts.put_back(t);
                return left;
        }
    }
    return left;
}

double primary()
{
    double result = 0.0;
    bool negative = false;
    int decimal = 0;
    Token t = ts.get();
    if (t.kind == '(') {
        result = expression();
        t = ts.get();
        if (t.kind != ')') {
            throw std::invalid_argument("matching paranthesis not found.");
        }
        return result;
    } else {
        if (t.kind == '-') {
            negative = true;
        }
        result = t.value;
        t = ts.get();
        while ((t.kind == 'n') || t.kind == '.') {
            if (t.kind == '.') {
                decimal = 10;
            } else {
                if (decimal > 0) {
                    result += t.value / decimal;
                    decimal *= 10;
                } else {
                    result *= 10;
                    result += t.value;
                }
            }
            t = ts.get();
        }
        if (negative) {
            result = -1 * result;
        }
        ts.put_back(t);
    }

    return result;
}

TEST_CASE( "r", "[digit]" ) {
    REQUIRE(calculate("4") == 4);
    REQUIRE(calculate("6") == 6);
    REQUIRE(calculate("4+2") == 6);
    REQUIRE(calculate("4+2+2") == 8);
    REQUIRE(calculate("4+2+2+4+2+2+1") == 17);
    REQUIRE(calculate("4-2") == 2);
    REQUIRE(calculate("8-2") == 6);
    REQUIRE(calculate("8-2-2") == 4);
    REQUIRE(calculate("3*2") == 6);
    REQUIRE(calculate("3*3") == 9);
    REQUIRE(calculate("3*2*3") == 18);
    REQUIRE(calculate("3+2*4") == 11);
    REQUIRE(calculate("3*2+4") == 10);
    REQUIRE(calculate("4 + 2") == 6);
    REQUIRE(calculate("10 + 2") == 12);
    REQUIRE(calculate("10 + 123") == 133);
    REQUIRE(calculate("-4 + 5") == 1);
    REQUIRE(calculate("-100 + 5") == -95);
    REQUIRE(calculate("-123 + 5") == -118);
    REQUIRE(calculate("(4 + 5)*2") == 18);
    REQUIRE(calculate("3+(-4 * 5)") == -17);
    REQUIRE(calculate("1.5 * 2") == 3);
    CHECK_THROWS(calculate("3/0"));
    // .5 * 2
}
