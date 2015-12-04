/*
 * File:   string_to_digitTest.cpp
 * Author: richi
 *
 * Created on Sep 17, 2015, 11:25:10 PM
 */

#include "string_to_digitTest.h"
#include <string>
#include "main.h"

using std::string;


CPPUNIT_TEST_SUITE_REGISTRATION(string_to_digitTest);

string_to_digitTest::string_to_digitTest() {
}

string_to_digitTest::~string_to_digitTest() {
}

void string_to_digitTest::setUp() {
}

void string_to_digitTest::tearDown() {
}

void string_to_digitTest::testGoodCases() {
    CPPUNIT_ASSERT_EQUAL( 0, string_to_digit( "zero" ) );
    CPPUNIT_ASSERT_EQUAL( 1, string_to_digit( "one" ) );
    CPPUNIT_ASSERT_EQUAL( 2, string_to_digit( "two" ) );
    CPPUNIT_ASSERT_EQUAL( 3, string_to_digit( "three" ) );
    CPPUNIT_ASSERT_EQUAL( 4, string_to_digit( "four" ) );
    CPPUNIT_ASSERT_EQUAL( 5, string_to_digit( "five" )  );
    CPPUNIT_ASSERT_EQUAL( 6, string_to_digit( "six" )  );
    CPPUNIT_ASSERT_EQUAL( 7, string_to_digit( "seven" )  );
    CPPUNIT_ASSERT_EQUAL( 8, string_to_digit( "eight" )  );
    CPPUNIT_ASSERT_EQUAL( 9, string_to_digit( "nine" )  );
}

void string_to_digitTest::testRubbish() {
    CPPUNIT_ASSERT_EQUAL( -1, string_to_digit( "Rubbish" ) );
    CPPUNIT_ASSERT_EQUAL( -1, string_to_digit( "Eins" ) );
    CPPUNIT_ASSERT_EQUAL( -1, string_to_digit( "One" ) );
}

