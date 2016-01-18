
//
// This is example code from Chapter 6.7 "Trying the second version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

/*
	This file is known as calculator02buggy.cpp

	I have inserted 5 errors that should cause this not to compile
	I have inserted 3 logic errors that should cause the program to give wrong results

	First try to find an remove the bugs without looking in the book.
	If that gets tedious, compare the code to that in the book (or posted source code)

	Happy hunting!

*/


#include<iostream>
#include<string>
#include<stdexcept>

// since I removed std_lib_facilities.h I have to define my own error function, lets make it simple 
inline void error(const std::string& s)
{
	std::cerr<<"Error: "<<s<<std::endl;
}



//------------------------------------------------------------------------------

/* 
    KD: 1st compilation failure error found 
    KD:
    KD:    lass -> class  
    KD:
*/
class Token { 
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }    
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public: 
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

/* 
    KD: 2nd compilation failure error  found 
    KD:
    KD: Token  get() -> Token Token_stream:: get() 
    KD:
    KD: Since we use here attribute full of object Token_stream 
    KD: we have to say that this method belongs to  Token_stream class
    KD:
*/
Token Token_stream:: get() 
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full=false;
        return buffer;
    } 

    char ch;
    std::cin>> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case '=':    // for "print"
    case 'x':    // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/': 
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '9':
        {    
            std::cin.putback(ch);         // put digit back into the input stream
            double val;
            std::cin>> val;              // read a floating-point number
            return Token('8',val);   // let '8' represent "a number"
        }
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback() 

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
        {    
            double d = expression();
            t = ts.get();
/* 
    KD: 3rd compilation failure error found
    KD:
    KD:  error("')' expected expected); ->  error("')' expected ");
    KD:
*/
            if (t.kind != ')') error("')' expected "); 
           
            return d;
        }
    case '8':            // we use '8' to represent a number
        return t.value;  // return the number's value
    default:
        error("primary expected");
    }
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
/* 
    KD: 1st logic error found
    KD: here we have to add break;
    KD: otherwise we end up in the endless loop
    KD:
*/     
             break;    
        case '/':
          {
            double d = primary();
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
/* 
    KD: 4th  compilation failure error found 
    KD: term(; -> term(); 
    KD: 
*/
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {    
        switch(t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
/* 
    KD: 2nd logic error found
    KD: 
    KD: left += term(); ->  left -= term();  
    KD: 
*/ 
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

int main()
{
// KD: Add a greeting line in main():
  std::cout<<"Welcome to our simple calculator.\n"<< 
             "The following operations are supported: (),\n"<<
             "*, /, +, -. Character = is a printing command and x\n"<< 
             "is a keyword which teminates the program.\n"<< 
             "Please enter expressions using floating-point numbers."<<std::endl;
  try
  {
/* 
    KD: 5th compilation failure error found 
    KD: we have to define variable val
    KD:
*/
    double val=0; 
    while (std::cin) {
        Token t = ts.get();
/*  KD: Change the character used as the exit command from q to x */
        if (t.kind == 'x') break; // 'x' for quit
/*  KD: Change the character used as the print command from ; to = */   
        if (t.kind == '=')        // '=' for "print now"
            std::cout << "=" << val << '\n';
/*
    KD: 3rd logic error        
    KD: The following block is not correct
    KD: else
    KD:    ts.putback(t);
    KD: val = expression(); 
    KD: In case a full expression is read like for example 2/3;
    KD: result is printed (so far correct)
    KD: In case a user want to terminate the program by writing q
    KD: this q is put back to Token stream. Still in the same iteration expession is executed      
    KD: and Token q  is read. Since q is not a  valid primary() the following message is printed:
    KD:
    KD: Error: primary expected
    KD: 
    KD: Expression:
    KD: else
    KD:    ts.putback(t);
    KD: val = expression(); 
    KD:
    KD: Should be changed to 
    KD: else
    KD: {
    KD:    ts.putback(t);
    KD:    val = expression();  
    KD: }
*/        

        else
        {
           ts.putback(t);
           val = expression();  
        }
    }
	//keep_window_open();
 }

 catch (std::exception& e) {
    std::cerr << "error: " << e.what() << '\n'; 
	//keep_window_open();
    return 1;
 }
 catch (...) {
    std::cerr << "Oops: unknown exception!\n"; 
	//keep_window_open();
    return 2;
 }
}
//------------------------------------------------------------------------------
