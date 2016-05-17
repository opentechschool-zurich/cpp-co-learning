#include <iostream>
#include "dowel.h"
#include "saw.h"

int main(int argc, char *argv[])
{
    Saw mysaw;

    Dowel stockpiece_1(1200);
    Dowel stockpiece_2(450);

    int part_length = 180;
    Dowel *part = nullptr;

    std::cout << "Bevfor" << "\n";
    std::cout << "Dowel 1: " << stockpiece_1.getlength() << "mm" << std::endl;
    std::cout << "Dowel 2: " << stockpiece_2.getlength() << "mm" << std::endl;

    std::cout << "Now we cut a " << part_length << "mm" << " long piece from Dowel 1" << std::endl;
    if (mysaw.cut(stockpiece_1, part, part_length != 0)) {
      std::cout << "Error cutting dowel." << std::endl; 
    }
    else {
      std::cout << "After" << "\n";
      std::cout << "Dowel 1: " << stockpiece_1.getlength() << "mm" << std::endl;
      std::cout << "Dowel 2: " << stockpiece_2.getlength() << "mm" << std::endl;
    
      if (part != nullptr) {
         std::cout << part->getlength() << std::endl;
         delete part;
      }
      else {
         std::cout << "No part returned? Must be a bug." << std::endl;
      }
    }

}
