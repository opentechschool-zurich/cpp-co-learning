#include "coffee.h"

int main()
{
    auto coffe = addSugar(addCream(Coffee()));
    coffe.print();
}
