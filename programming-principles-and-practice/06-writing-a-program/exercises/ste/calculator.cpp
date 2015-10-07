//
//  calculator.cpp
//  MeetUpChapter6
//
//  Created by Stefano Ugolini on 06/10/15.
//  Copyright © 2015 Stefano Ugolini. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Token
{
    char type;
    double number;
};

bool Tokenizer(string& expression, vector<Token>& token_vect)
{
    size_t first_operand = expression.find_first_of("+-*/");
    
    // Check if there is an operand in the expression
    // In case there is, extract the number that precedes the operand and then the operand
    // Remove the operand and the number from the expression
    
    if(string::npos != first_operand)
    {
        double number = stod(expression.substr(0, first_operand));
        expression.erase(0,first_operand);
        
        char oper = expression.substr(0, 1).c_str()[0];
        expression.erase(0,1);
        
        token_vect.push_back(Token{'n',number});
        token_vect.push_back(Token{oper,0});
        
        return true;
    }
    else
    {
        return false;
    }
}

bool Calc(vector<Token>& token_vect)
{

    for(vector<Token>::iterator it = token_vect.begin(); it != token_vect.end(); it++)
    {
        if('*'==it->type)
        {
            it->number = (it-1)->number * (it+1)->number;
            it->type = 'n';
            token_vect.erase(it - 1);
            token_vect.erase(it);
            return true;
        }
    }
    
    for(vector<Token>::iterator it = token_vect.begin(); it != token_vect.end(); it++)
    {
        if('/'==it->type)
        {
            it->number = (it-1)->number / (it+1)->number;
            it->type = 'n';
            token_vect.erase(it - 1);
            token_vect.erase(it);
            return true;
        }
    }

    for(vector<Token>::iterator it = token_vect.begin(); it != token_vect.end(); it++)
    {
        if('+'==it->type)
        {
            it->number = (it-1)->number + (it+1)->number;
            it->type = 'n';
            token_vect.erase(it - 1);
            token_vect.erase(it);
            return true;
        }
    }
    
    for(vector<Token>::iterator it = token_vect.begin(); it != token_vect.end(); it++)
    {
        if('-'==it->type)
        {
            it->number = (it-1)->number - (it+1)->number;
            it->type = 'n';
            token_vect.erase(it - 1);
            token_vect.erase(it);
            return true;
        }
    }
    
    return false;
    
}

void PrintTokens(const vector<Token>& tokentoprint)
{
    for(Token tk : tokentoprint)
    {
        cout << tk.type << " " << tk.number << endl;
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {

    
    vector<Token> tokens;
    string expression;
    
    cout << "Expression\n>" << endl;
    
    //expression = "4.5*2+10-3*1.5";  //debug expression
    getline(cin, expression);
    
    
    while(Tokenizer(expression, tokens));
    
    //No more operands, add the last number to tokens
    tokens.push_back(Token{'n', stod(expression)});
    

    //PrintTokens(tokens);
    
    while(Calc(tokens))
    {
        //PrintTokens(tokens);
    }
    
    cout << "Result: " << tokens[0].number << endl;

    return 0;
}
