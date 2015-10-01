/*
 * File:   newtestclass.cpp
 * Author: Richard Eigenmann
 *
 * Created on Sep 29, 2015, 8:12:25 PM
 */

#include "newtestclass.h"
#include "../std_lib_facilities.h"

// Forward references for the stuff in main.cpp

class ImaginaryNumberException {
};

vector<double> quad_results (double a, double b, double c);

CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);


void newtestclass::testGoodCalculation() {
    vector<double> firstResults = quad_results(7.0, 3.0, 0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0, firstResults[0] , 0.000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.428571, firstResults[1] , 0.000001);
    
    vector<double> secondResults = quad_results(2.0, 5.0, 3.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1, secondResults[0], 0.000001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.5, secondResults[1], 0.000001);
}

void newtestclass::testImaginaryNumber() {
    try {
        vector<double> no_result = quad_results(4.0, 5.0, 3.0);
    } catch (ImaginaryNumberException) {
        CPPUNIT_ASSERT(true);
        return;
    }
    // the computer should never get here
    cerr << " There is no real number result for the quadratic equation a=4, b=5, c=3 - An exception should have been thrown!\n";
    CPPUNIT_ASSERT(false);
}

