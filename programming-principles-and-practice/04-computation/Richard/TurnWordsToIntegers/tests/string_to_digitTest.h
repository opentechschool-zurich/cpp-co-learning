/*
 * File:   string_to_digitTest.h
 * Author: richi
 *
 * Created on Sep 17, 2015, 11:25:10 PM
 */

#ifndef STRING_TO_DIGITTEST_H
#define	STRING_TO_DIGITTEST_H

#include <cppunit/extensions/HelperMacros.h>

class string_to_digitTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(string_to_digitTest);

    CPPUNIT_TEST(testGoodCases);
    CPPUNIT_TEST(testRubbish);

    CPPUNIT_TEST_SUITE_END();

public:
    string_to_digitTest();
    virtual ~string_to_digitTest();
    void setUp();
    void tearDown();

private:
    void testGoodCases();
    void testRubbish();
};

#endif	/* STRING_TO_DIGITTEST_H */

