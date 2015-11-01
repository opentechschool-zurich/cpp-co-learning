/*
Calculator Programm: 

It implements the following grammar: 

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

#include <iostream>
#include <string>
#include <exception>
#include <vector>

using namespace std;

void error(string message){

}

//------------------------------------------------------------------------------

class Token {
public:
    char token_exept_number;       
    double number;     
    Token(char zeichen)    // make a Token from a char
        :token_exept_number_of_token(zeichen), number(0) { }    
    Token(char zeichen, double val)     // make a Token from a char and a double
        :token_exept_number(zeichen), number(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public: 
    Token_stream();   // make a Token_stream that reads from cin   // read_cin
    Token get_next_Token();     
    void putback(Token t);    
private:
    bool token_in_buffer;       
    Token token_buffer;     
};

//------------------------------------------------------------------------------

// The constructor just sets token_in_buffer to indicate that the token_buffer is empty:
Token_stream::Token_stream(): token_in_buffer(false), token_buffer(0)    
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's token_buffer:
void Token_stream::putback(Token new_token)
{
    if (token_in_buffer){
		error("there is already a token in buffer");
	}
    token_buffer = new_token;      
    token_in_buffer = true;     
}

//------------------------------------------------------------------------------

Token Token_stream::get_next_Token()
{
  
    if (token_in_buffer) {        
        token_in_buffer=false;
        return token_buffer;
    } 

    char zeichen;
    cin >> zeichen;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (zeichen) {
    case ';':    // for "print"
    case 'x':    // for "quit"
    case '!':
    case '(':
	case ')':
	case '+': 
	case '-': 
	case '*': 
	case '/': 
	case '{':
	case '}':
        return Token(zeichen);        
    case '.':
    case '0': 
	case '1': 
	case '2': 
	case '3': 
	case '4':
    case '5': 
	case '6': 
	case '7': 
	case '8': 
	case '9':
        {    
            cin.putback(zeichen);         // put digit back into the input stream
            double value;
            cin >> value;              // read a floating-point number
            return Token(number_type,value);   // let '8' represent "a number"
        }
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

Token_stream stream;        // provides get_next_Token() and putback() 

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()
int myfactorial(int n); 

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
  Token t = stream.get_next_Token();
  switch (t.token_exept_number) {
  case '(':    // handle '(' expression ')'
    {    
      double d = expression();
      t = stream.get_next_Token();
      if (t.token_exept_number != ')') error("')' expected");
      return d;
    }
  case '{':    // handle '{' expression '}'
    {    
      double d = expression();
      t = stream.get_next_Token();
      if (t.token_exept_number != '}') error("'}' expected");
      return d;
    }
  case number_type:            // we use '8' to represent a number
    {
      double nummer = t.number; 
      return nummer;  
    }
  default:
    error("primary expected");
  }
    
}

//------------------------------------------------------------------------------

// deal with factorials

double secondary()
{
  double left = primary(); 

  Token t = stream.get_next_Token();

  if (t.token_exept_number == '!') 
    return myfactorial(left); 

  stream.putback(t);     // put t back into the token stream
  return left;
  
}



//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = secondary();
    Token t = stream.get_next_Token();        // get_next_Token the next token from token stream

    while(true) {
        switch (t.token_exept_number) {
        case '*':
            left *= secondary();
            t = stream.get_next_Token();
            break;
        case '/':
            {    
                double d = secondary();
                if (d == 0) error("divide by zero");
                left /= d; 
                t = stream.get_next_Token();
                break;
            }
        default: 
            stream.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
  double left = term();      // read and evaluate a Term
  Token token = stream.get_next_Token();        // get_next_Token the next token from token stream

  while(true) {    
    switch(token.token_exept_number) {
    case '+':
      left += term();    // evaluate Term and add
      token = stream.get_next_Token();
      break;
    case '-':
      left -= term();    // evaluate Term and subtract
      token = stream.get_next_Token();
      break;
    default: 
      stream.putback(t);     // put t back into the token stream
      return left;       // finally: no more + or -: return the answer
    }
  }
}

//------------------------------------------------------------------------------

int main()
{
  cout << "Welcome to our simple calculator.\n"
       << "Please enter expressions using floating-point numbers\n"
       << "and operators +,-,*, / and !.\n\n"
       << "Type x to exit and ; to print." << endl; 

  try
    {
      double val = 0;
      while (cin) {
        Token t = stream.get_next_Token();

        if (t.token_exept_number == 'x') break; // 'x' for quit
        if (t.token_exept_number == ';')        // ';' for "print now"
          {
            cout << "=" << val << '\n';
            continue;
          }
        else
          stream.putback(t);
        
        val = expression();
      }
    }
  catch (exception& e) {
    cerr << "error: " << e.what() << '\n';  
    return 1;
  }
  catch (...) {
    cerr << "Oops: unknown exception!\n";  
    return 2;
  }
}
//------------------------------------------------------------------------------


int myfactorial(int n){
  if (n < 0) error("factorial only defined for positive ints"); 
  if (n == 0) return 1;
  else
    return n*myfactorial(n-1); 
}
