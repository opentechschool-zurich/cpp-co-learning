/*
 * File:   newtestclass.h
 * Author: Richard Eigenmann
 *
 * Created on Sep 29, 2015, 8:12:23 PM
 */

#ifndef NEWTESTCLASS_H
#define	NEWTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass);

    CPPUNIT_TEST(testGoodCalculation);
    CPPUNIT_TEST(testImaginaryNumber);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass();
    virtual ~newtestclass();
    void setUp();
    void tearDown();

private:
    void testGoodCalculation();
    void testImaginaryNumber();
};

#endif	/* NEWTESTCLASS_H */

