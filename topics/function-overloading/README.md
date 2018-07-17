# Function overloading

Sololearn's example:

```cpp
#include <iostream>

void printNumber(int x)
{
    std::cout << "Printing an integer" << x << std::endl;
}


void printNumber(float x)
{
    std::cout << "Printing a float" << x << std::endl;
}


int main()
{
    int a = 16;
    float b = 54.541;
    printNumber(a);
    printNumber(b);
}
```

Possible topics to better understand the Sololearn chapter:

- Write and compile a first C++ progam (eventually, install Codeblocks).
- `main()` with no return.
- Include `<iostream>` and explicitly mentioning `std`
- Typing this code and getting it to compile and run on her computer.
- Differences between `int` and `float`.
- Why is it possible to have two functions called `printNumber()`?
- Create a `sum()` function that works for both `int` and `float`?
  - What happens if we have two overloaded functions?
  - What happens if we only have one `sum(int, int)` function?
  - And with only one `sum(float, float)` function?
  - What happens if we have both `sum()` function but switch the order?
  - Create a sum that accepts the strings `one` to `nine`.
