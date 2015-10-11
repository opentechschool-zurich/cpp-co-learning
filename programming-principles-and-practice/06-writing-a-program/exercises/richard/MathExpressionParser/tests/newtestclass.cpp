/*
 * File:   newtestclass.cpp
 * Author: Richard Eigenmann
 *
 * Created on Oct 4, 2015, 9:29:40 PM
 */

#include "newtestclass.h"
#include "../std_lib_facilities.h"
//#include "../main.cpp"

class Token {
public:
    char kind;
    double value;

    Token(char ch)
    : kind(ch), value(0) {
    }

    Token(char ch, double val)
    : kind(ch), value(val) {
    }
};

vector<Token> parseExpression(string expression);
vector<Token> reduceTerms(vector<Token> tokens);
vector<Token> reduceExpressions(vector<Token> tokens);
double parseMathExpression(string expression);
    

CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass() {
}

newtestclass::~newtestclass() {
}

void newtestclass::setUp() {
}

void newtestclass::tearDown() {
}

void newtestclass::testSingleNumber() {
    vector<Token> tokens = parseExpression("6");
    CPPUNIT_ASSERT_MESSAGE("Expecting 1 token for expression 6", 1 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting type to be d", 'd' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting value to be 6", 6 == tokens[0].value);
    
    CPPUNIT_ASSERT_MESSAGE("Expecting result of 6 to be 6.0", 6.0 == parseMathExpression("6"));
}

void newtestclass::testNegativeNumber() {
    vector<Token> tokens = parseExpression("-6");
    CPPUNIT_ASSERT_MESSAGE("Expecting 2 tokens for expression -6", 2 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting type to be -", '-' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting value to be 0", 0 == tokens[0].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting type to be d", 'd' == tokens[1].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting value to be 6", 6 == tokens[1].value);
    
    //CPPUNIT_ASSERT_MESSAGE("Expecting result of -6 to be -6.0", -6.0 == parseMathExpression("-6"));
}

void newtestclass::testTwoDigitNumber() {
    vector<Token> tokens = parseExpression("62");
    CPPUNIT_ASSERT_MESSAGE("Expecting 1 token for expression 62", 1 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting type to be d", 'd' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting value to be 62", 62 == tokens[0].value);
}

void newtestclass::test5DigitNumber() {
    vector<Token> tokens = parseExpression("12345");
    CPPUNIT_ASSERT_MESSAGE("Expecting 1 token for expression 12345", 1 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting type to be d", 'd' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting value to be 12345", 12345 == tokens[0].value);
}

void newtestclass::test16DigitNumber() {
    vector<Token> tokens = parseExpression("1234567890123456");
    CPPUNIT_ASSERT_MESSAGE("Expecting 1 token for expression 1234567890123456", 1 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting type to be d", 'd' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting value to be 1234567890123456", 1234567890123456 == tokens[0].value);
}

void newtestclass::testAddition() {
    vector<Token> tokens = parseExpression("6+4");
    CPPUNIT_ASSERT_MESSAGE("Expecting 3 tokens for expression 6+4", 3 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type d", 'd' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 6", 6 == tokens[0].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to be type +", '+' == tokens[1].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to have value 0", 0 == tokens[1].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to be type d", 'd' == tokens[2].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to have value 4", 4 == tokens[2].value);

    vector<Token> reducedTokens = reduceExpressions(tokens);
    CPPUNIT_ASSERT_MESSAGE("Expecting 1 token for reduced 6+4 tokens", 1 == reducedTokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type d", 'd' == reducedTokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 10", 10 == reducedTokens[0].value);

}

void newtestclass::testMultiAddition() {
    vector<Token> tokens = parseExpression("6+4+2");
    CPPUNIT_ASSERT_MESSAGE("Expecting 5 tokens for expression 6+4+2", 5 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type d", 'd' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 6", 6 == tokens[0].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to be type +", '+' == tokens[1].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to have value 0", 0 == tokens[1].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to be type d", 'd' == tokens[2].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to have value 4", 4 == tokens[2].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 3 to be type +", '+' == tokens[3].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 3 to have value 0", 0 == tokens[3].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 4 to be type d", 'd' == tokens[4].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 4 to have value 2", 2 == tokens[4].value);

    vector<Token> reducedTokens = reduceExpressions(tokens);
    CPPUNIT_ASSERT_MESSAGE("Expecting 1 token for reduced 6+4+2 tokens", 1 == reducedTokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type d", 'd' == reducedTokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 12", 12 == reducedTokens[0].value);
}

void newtestclass::testSubtraction() {
    vector<Token> tokens = parseExpression("6-4");
    CPPUNIT_ASSERT_MESSAGE("Expecting 3 tokens for expression 6-4", 3 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type d", 'd' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 6", 6 == tokens[0].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to be type -", '-' == tokens[1].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to have value 0", 0 == tokens[1].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to be type d", 'd' == tokens[2].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to have value 4", 4 == tokens[2].value);

    vector<Token> reducedTokens = reduceExpressions(tokens);
    CPPUNIT_ASSERT_MESSAGE("Expecting 1 token for reduced 6-4 tokens", 1 == reducedTokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type d", 'd' == reducedTokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 2", 2 == reducedTokens[0].value);
}

void newtestclass::testMultiplication() {
    vector<Token> tokens = parseExpression("6*4");
    CPPUNIT_ASSERT_MESSAGE("Expecting 3 tokens for expression 6*4", 3 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type d", 'd' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 6", 6 == tokens[0].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to be type *", '*' == tokens[1].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to have value 0", 0 == tokens[1].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to be type d", 'd' == tokens[2].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to have value 4", 4 == tokens[2].value);

    vector<Token> reducedTokens = reduceTerms(tokens);
    CPPUNIT_ASSERT_MESSAGE("Expecting 1 token for reduced 6*4 tokens", 1 == reducedTokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type d", 'd' == reducedTokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 24", 24 == reducedTokens[0].value);
}

void newtestclass::testMultiMultiplication() {
    vector<Token> tokens = parseExpression("6*4*2");
    CPPUNIT_ASSERT_MESSAGE("Expecting 5 tokens for expression 6*4*2", 5 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type d", 'd' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 6", 6 == tokens[0].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to be type *", '*' == tokens[1].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to have value 0", 0 == tokens[1].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to be type d", 'd' == tokens[2].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to have value 4", 4 == tokens[2].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 3 to be type *", '*' == tokens[3].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 3 to have value 0", 0 == tokens[3].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 4 to be type d", 'd' == tokens[4].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 4 to have value 2", 2 == tokens[4].value);

    vector<Token> reducedTokens = reduceTerms(tokens);
    CPPUNIT_ASSERT_MESSAGE("Expecting 1 token for reduced 6*4*2 tokens", 1 == reducedTokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type d", 'd' == reducedTokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 48", 48 == reducedTokens[0].value);
}

void newtestclass::testDivision() {
    vector<Token> tokens = parseExpression("6/4");
    CPPUNIT_ASSERT_MESSAGE("Expecting 3 tokens for expression 6/4", 3 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type d", 'd' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 6", 6 == tokens[0].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to be type /", '/' == tokens[1].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to have value 0", 0 == tokens[1].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to be type d", 'd' == tokens[2].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to have value 4", 4 == tokens[2].value);

    vector<Token> reducedTokens = reduceTerms(tokens);
    CPPUNIT_ASSERT_MESSAGE("Expecting 1 token for reduced 6/4 tokens", 1 == reducedTokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type d", 'd' == reducedTokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 1.5", 1.5 == reducedTokens[0].value);
}

void newtestclass::testBracketsSingleNumber() {
    vector<Token> tokens = parseExpression("(6)");
    CPPUNIT_ASSERT_MESSAGE("Expecting 3 tokens for expression (6)", 3 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type (", '(' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 0", 0 == tokens[0].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to be type d", 'd' == tokens[1].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to have value 6", 6 == tokens[1].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to be type )", ')' == tokens[2].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to have value 0", 0 == tokens[2].value);
}

void newtestclass::testBracketsAddition() {
    vector<Token> tokens = parseExpression("(6+3)");
    CPPUNIT_ASSERT_MESSAGE("Expecting 5 tokens for expression (6+3)", 5 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type (", '(' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 0", 0 == tokens[0].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to be type d", 'd' == tokens[1].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to have value 6", 6 == tokens[1].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to be type +", '+' == tokens[2].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to have value 0", 0 == tokens[2].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 3 to be type d", 'd' == tokens[3].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 3 to have value 3", 3 == tokens[3].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 4 to be type )", ')' == tokens[4].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 4 to have value 0", 0 == tokens[4].value);
}

void newtestclass::testBracketsAtEnd() {
    vector<Token> tokens = parseExpression("4+(6+3)");
    CPPUNIT_ASSERT_MESSAGE("Expecting 7 tokens for expression 4+(6+3)", 7 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type d", 'd' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 4", 4 == tokens[0].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to be type +", '+' == tokens[1].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to have value 0", 0 == tokens[1].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to be type (", '(' == tokens[2].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to have value 0", 0 == tokens[2].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 3 to be type d", 'd' == tokens[3].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 3 to have value 6", 6 == tokens[3].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 4 to be type +", '+' == tokens[4].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 4 to have value 0", 0 == tokens[4].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 5 to be type d", 'd' == tokens[5].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 5 to have value 3", 3 == tokens[5].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 6 to be type )", ')' == tokens[6].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 6 to have value 0", 0 == tokens[6].value);
}

void newtestclass::testBracketsAtStart() {
    vector<Token> tokens = parseExpression("(6+3)+4");
    CPPUNIT_ASSERT_MESSAGE("Expecting 7 tokens for expression (6+3)+4", 7 == tokens.size());
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to be type (", '(' == tokens[0].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 0 to have value 0", 0 == tokens[0].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to be type d", 'd' == tokens[1].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 1 to have value 6", 6 == tokens[1].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to be type +", '+' == tokens[2].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 2 to have value 0", 0 == tokens[2].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 3 to be type d", 'd' == tokens[3].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 3 to have value 3", 3 == tokens[3].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 4 to be type )", ')' == tokens[4].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 4 to have value 0", 0 == tokens[4].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 5 to be type +", '+' == tokens[5].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 5 to have value 0", 0 == tokens[5].value);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 6 to be type d", 'd' == tokens[6].kind);
    CPPUNIT_ASSERT_MESSAGE("Expecting token 6 to have value 4", 4 == tokens[6].value);
}
