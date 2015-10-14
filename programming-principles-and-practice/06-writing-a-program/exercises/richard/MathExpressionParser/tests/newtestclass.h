/*
 * File:   newtestclass.h
 * Author: richi
 *
 * Created on Oct 4, 2015, 9:29:40 PM
 */

#ifndef NEWTESTCLASS_H
#define	NEWTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass);

    CPPUNIT_TEST(testSingleNumber);
    CPPUNIT_TEST(testNegativeNumber);
    CPPUNIT_TEST(testTwoDigitNumber);
    CPPUNIT_TEST(test5DigitNumber);
    CPPUNIT_TEST(test16DigitNumber);
    
    CPPUNIT_TEST(testAddition);
    CPPUNIT_TEST(testMultiAddition);
    CPPUNIT_TEST(testSubtraction);
    CPPUNIT_TEST(testMultiplication);
    CPPUNIT_TEST(testMultiMultiplication);
    CPPUNIT_TEST(testDivision);
    
    CPPUNIT_TEST(testBracketsSingleNumber);
    CPPUNIT_TEST(testBracketsAddition);
    CPPUNIT_TEST(testBracketsAtEnd);
    CPPUNIT_TEST(testBracketsAtStart);
    
    CPPUNIT_TEST(testNasty);
    
    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass();
    virtual ~newtestclass();
    void setUp();
    void tearDown();

private:
    void testSingleNumber();
    void testNegativeNumber();
    void testTwoDigitNumber();
    void test5DigitNumber();
    void test16DigitNumber();
    void testAddition();
    void testMultiAddition();
    void testSubtraction();
    void testMultiplication();
    void testMultiMultiplication();
    void testDivision();
    void testBracketsSingleNumber();
    void testBracketsAddition();
    void testBracketsAtEnd();
    void testBracketsAtStart();
    void testNasty();
};

#endif	/* NEWTESTCLASS_H */

