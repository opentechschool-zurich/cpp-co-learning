/*
 * Decorator.hpp
 *
 *  Created on: Jul 26, 2016
 *      Author: arktis
 */

#ifndef OPENTECH_SCHOOL_DECORATOR_HPP_
#define OPENTECH_SCHOOL_DECORATOR_HPP_
#include <iostream>

namespace meetup {
namespace opentechschool {

class Coffee {
public:
	Coffee() {}
	void print() const   { std::cout<<"Delivering Coffee.."<<std::endl; }
};

template <class T>
class CreamDecorator {
public:
	CreamDecorator(const T& x): nested(x) {}
	void print() const { nested.print(); std::cout<<" with Cream."<<std::endl;}
private:
	const T& nested;
};

template <class T>
class SugarDecorator {
public:
	SugarDecorator(const T& x): nested(x) {}
	void print() const { nested.print(); std::cout<<" with Sugar."<<std::endl;}
private:
	const T& nested;
};

} //opentechschool
} // meetup



#endif /* OPENTECH_SCHOOL_DECORATOR_HPP_ */
