#ifndef DOWEL_H
#define DOWEL_H
#include <exception>

class invalidlength: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Invalid length";
    }
};

class Dowel 
{
private:
    int length;
    Dowel();

public:
    Dowel( int length);
    int getlength();
    int setlength(int newlength);
};

#endif // DOWEL_H
