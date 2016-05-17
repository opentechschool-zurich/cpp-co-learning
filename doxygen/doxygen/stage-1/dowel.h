#ifndef DOWEL_H
#define DOWEL_H
#include <exception>

/// I do not like this form of declaration of exceptions.
/// I do not like it to be a class in my doxygen documentation.
class invalidlength: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Invalid length";
    }
};

/*! 
A Dowel is a cylindrical peace of wood. 
I have seeral Dowels as stock material. 
For production pieces are cut from the dowels. 
After a cut is done there exist two Dowels:
The original one which is shorter now,
a "new" Dowel to be used in production.
This Dowels are cut in twobe used in production of some furniture
All my Dowels have the same diameter, but the have differnt length.
*/
class Dowel 
{
private:
    int length;
    Dowel();

public:
    Dowel( int length);
    int getlength();
    /** 
     * The length of a Dowel changes when it gets cut by a saw.
     * I want to nurror the physical world in this program.
     * A Dowel is not able to cut itself.
     * A saw does the cut. The saw should change (shorten) the length of a Dowel.
     * As I want to model the physical world in this program,
     * a saw should be able to shorten a Dowel, but this
     * function should not be available to everybody.
     * A Dowel can not cut itself, a tool does the work.
     */ 
    int setlength(int newlength);
};

#endif // DOWEL_H
