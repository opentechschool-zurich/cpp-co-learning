// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "std_lib_facilities.h"
#include <sstream>

/*
Calculator Programm:

It implements the following grammar:

Statement:
	Expression
	Print
	Quit
	Help

Print:
	;

Quit:
	q

Help:
	h

Expression:
----------------

Term
Expression '+' Term
Expression '-' Term

Term:
----------------

Secondary
Term '*' Secondary
Term '/' Secondary


Secondary:
----------------

Primary
Primary'!'

Primary:
----------------

Number
'(' expression ')'
'{' expression '}'

Number:
----------------

floating-point-literal


*/



//------------------------------------------------------------------------------

const char KIND_NUMBER = '8';

const char KIND_HELP = 'h';
const char KIND_EXIT = 'x';
const char KIND_PRINT = ';';

const string WELCOME_MESSAGE = string("Welcome to our simple calculator.\n")
+ string("Press h for help\n");


const string HELP_MESSAGE = "Keyboard Expression Calculator\n"
"Help Key:\th\n"
"Print:\t;\n"
"Exit:\tx\n"
"Please enter expressions using floating-point numbers\n"
"and operators +,-,*, / and !.\n\n"
"Examples:\n"
"4.2+8.3\n"
"4*(2+6.5)\n"
"2+3!\n"
;

class Token {
public:
	char kind;        // what kind of token
	double value;     // the value if it's KIND_NUMBER
	Token(char ch)    // make a Token from a char
		:kind(ch), value(0) { }
	Token(char ch, double val)
		:kind(ch), value(val) { }
};

/*------------------------------------------------------------------------------
Create a class Token_stream with methods get() and putback() that allows
us to read cin and parse it into Tokens.
*/

class Token_stream {
public:
	Token_stream();
	Token get();
	void putback(Token t);
private:
	bool hasPendingToken;
	Token pendingToken;     // here is where we keep a Token put back using putback()
};
Token_stream::Token_stream()
	:hasPendingToken(false), pendingToken(0) {}

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token putbackToken) {
	if (hasPendingToken) error("putback() into a full buffer");
	pendingToken = putbackToken;
	hasPendingToken = true;
}

Token Token_stream::get() {
	if (hasPendingToken) {
		hasPendingToken = false;
		return pendingToken;
	}

	char ch;
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
	case KIND_PRINT:
	case KIND_EXIT:
	case KIND_HELP:
	case '!':
	case '(': case ')': case '+': case '-': case '*': case '/': case '{': case '}':
		return Token(ch);        // let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		/* put the char back into the input stream
		   read from cin into a double until a character 
		   doesn't fit i.e. If the char is 1 read every
		   char in cin to the "val" double until say a + is
		   encountered. The + char hangs around in cin until 
		   the next loop iteration. */
		cin.putback(ch);
		double val;
		cin >> val;
		return Token(KIND_NUMBER, val);
	}
	default:
		error("No function for char: " + ch);
	}
}

//------------------------------------------------------------------------------

Token_stream ts;         

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()
int myfactorial(int n);

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary() {
	Token t = ts.get();
	switch (t.kind) {
	case '(':    // handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '{':    // handle '{' expression '}'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != '}') error("'}' expected");
		return d;
	}
	case KIND_NUMBER:
	{
		double d = t.value;
		return d;  // return the number's value
	}
	default:
		error("primary expected");
	}

}

//------------------------------------------------------------------------------

// deal with factorials

double secondary() {
	double left = primary();

	Token t = ts.get();

	if (t.kind == '!')
		return myfactorial(left);

	ts.putback(t);     // put t back into the token stream
	return left;
}



//------------------------------------------------------------------------------

// deal with *, /, and %
double term() {
	double left = secondary();
	Token t = ts.get();        // get the next token from token stream

	while (true) {
		switch (t.kind) {
		case '*':
			left *= secondary();
			t = ts.get();
			break;
		case '/':
		{
			double d = secondary();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);     // put t back into the token stream
			return left;
		}
	}
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
	double left = term();      // read and evaluate a Term
	Token t = ts.get();        // get the next token from token stream

	while (true) {
		switch (t.kind) {
		case '+':
			left += term();    // evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left -= term();    // evaluate Term and subtract
			t = ts.get();
			break;
		default:
			ts.putback(t);     // put t back into the token stream
			return left;       // finally: no more + or -: return the answer
		}
	}
}

//------------------------------------------------------------------------------

int main() {
	cout << WELCOME_MESSAGE;
	try {
		double val = 0;
		while (cin) {
			Token t = ts.get();

			if (t.kind == 'x') break; // 'x' for quit
			if (t.kind == KIND_HELP) {
				cout << HELP_MESSAGE;
				continue;
			}
			if (t.kind == ';')        // ';' for "print now"
			{
				cout << "=" << val << '\n';
				continue;
			}
			else
				ts.putback(t);

			val = expression();
		}
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (...) {
		cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2;
	}
	return 0;
}
//------------------------------------------------------------------------------


int myfactorial(int n) {
	if (n < 0) error("factorial only defined for positive ints");
	if (n == 0) return 1;
	else
		return n*myfactorial(n - 1);
}
