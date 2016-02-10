#include "Link.h"
#include <iostream>

using namespace std;

void printGods(Link* firstGod)
{
  Link* iteratorLink = firstGod;
  while (iteratorLink) {
    cout << iteratorLink->god << "; ";
    
    iteratorLink = iteratorLink->succ;
    
  }
  cout << endl;
}


void addGod(Link* firstGod, Link* newGod)
{
  Link* iteratorLink = firstGod;
  if (iteratorLink->succ == nullptr) {
    iteratorLink->succ = newGod;
    newGod->succ = nullptr;
    newGod->prev = iteratorLink;
    
    return;
  }

}

Link* findGod(string godToFind, Link* listOfGods)
{
  Link* iteratorLink = listOfGods;
  while (iteratorLink) {
    if (iteratorLink->god == godToFind) {
      return iteratorLink;
    }
    
    iteratorLink = iteratorLink->succ;
    
  }
  // nothing found
  return nullptr;
  
}

void insertBefore(Link* newGod, Link* godToBePushed)
{
  // get previous god
  Link* previousGod = godToBePushed->prev;
  
  newGod->prev = previousGod;
  newGod->succ = godToBePushed;
  
  previousGod->succ = newGod;
  godToBePushed->prev = newGod;
}

void unlinkGod(Link* godToDelete)
{
  Link* previousGod = godToDelete->prev;
  Link* nextGod = godToDelete->succ;
  
  if (previousGod) {
    previousGod->succ = nextGod;
    
  }
  if (nextGod) {
    nextGod->prev = previousGod;
  }
  
}

int main() {

  Link* norse_gods = new Link("Thor");
  printGods(norse_gods);
  
  Link* secondGod = new Link("Odin");
  addGod(norse_gods, secondGod);
  printGods(norse_gods);
  
  
  Link* foundGod = findGod("Odin", norse_gods);
  
  if (foundGod) {
    cout << "we found it: " << foundGod->god << endl;

    insertBefore( new Link("Frida"), foundGod);
    addGod( new Link("Frigg"), foundGod);
    
    printGods(norse_gods);
    
    unlinkGod(foundGod);
    delete foundGod;
    
    printGods(norse_gods);

  }else{
    cout << "didn't find Odin" << endl;
  }

  
  
  return 0;
  
}