#include "dowel.h"

Dowel::Dowel()
{
}

Dowel::Dowel(int dowellength)
{
      length = dowellength;
}


int Dowel::getlength() {
   return length;
}

int Dowel::setlength(int newlength) {
     length = newlength;
     return(0);
}


