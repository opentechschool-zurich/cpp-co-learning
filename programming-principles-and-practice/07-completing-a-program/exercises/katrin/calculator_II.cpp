/**
 * Calculator Version II
 * - cin is replaced by istringstream (input comes from test unit)
 * - uses catch for unit testing
 * - directly uses exceptions
 * - parses options
 */

// -------------------------------------------------------------------------------------------
// INCLUDES, DEFINES AND VARIABLES
// -------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <exception>
#include <sstream>
#include <vector>

#include "optionparser.h"
#define CATCH_CONFIG_RUNNER  // needed in catch.hpp
#include "catch.hpp"

using namespace std;

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
        "  calculator\n" },    {0,0,0,0,0,0}
};




// -------------------------------------------------------------------------------------------
// CLASS AND INSTANCES
// -------------------------------------------------------------------------------------------
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

Token t;
Token_stream ts;



double calculate(string calculation);
double expression();
double term();
double primary();


// -------------------------------------------------------------------------------------------
// MAIN
// -------------------------------------------------------------------------------------------
int main(int argc, char* argv[]) {

		// option parser
		argc -=(argc > 0);
		argv +=(argc > 0); 

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

		// start code
		string calculation;
		double result;

		cout << "Please enter an expression (RETURN to quit) :" << endl;

		// write cin in calculation
		while (getline(cin, calculation))
	    {
			if (calculation.empty()){
				break;
			}

			result = calculate(calculation);

			cout << "result: " << result << endl << "Please enter an expression (RETURN to quit): ";
		}
}


// -------------------------------------------------------------------------------------------
// FUNCTIONS
// -------------------------------------------------------------------------------------------

/*
 * Build stream from string
 */
void Token_stream::set(string line) { 
    full = false;  
    calculation.str(line);  
    calculation.clear();
}

/*
 * Get token in the size of a single digit number
 */
Token Token_stream::get() {
	char c;
    Token t;

    if (full) {
        full = false;
        return buffer;
    } 

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
		// no action       
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '.') {
        t.kind = c;
    } else if (c == '\0') {
        t.kind = 'q';
    } else {
        throw std::invalid_argument("just get out"); 
    }
    return t;
}

/*
 * Token not used and given back
 */
void Token_stream::put_back(Token t) {
    if (full) {
        throw std::overflow_error("buffer already full");
    }
    full = true;
    buffer = t;
}


/*
 * Basic function of the calculator
 */
double calculate(string calculation) {

    double result = 0.0;

    ts.set(calculation);
    result = expression();
    return result;
}

/*
 * Highest level in Grammar
 * Last priority: Handels + and -
 */
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


/*
 * Middle level in Grammar
 * Second Priority: Check * and /
 * which are prior to + and -
 */
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
                left /= primary();
                t = ts.get();
                break;
            default:
                ts.put_back(t);
                return left;
        }
    }
    return left;
}


/*
 * Lowest level in Grammar
 * Highest Priority: Read each digit
 * Destinguish between number and special character
 */
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
            } else if (negative) {
                result = -1 * t.value;
                negative = false;
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
        ts.put_back(t);
    }

    return result;
}

// -------------------------------------------------------------------------------------------
// Unit testing
// -------------------------------------------------------------------------------------------

/*
 * Each line is a new test
 */
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
    REQUIRE(calculate("(4 + 5)*2") == 18);
    REQUIRE(calculate("3+(-4 * 5)") == -17);
    REQUIRE(calculate("1.5 * 2") == 3);
}
