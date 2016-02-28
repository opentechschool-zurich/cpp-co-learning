# Draw an Acid Smiley using FLTK

This version of the ClassedAcidSmiley project avoids pointers.

The original problem that led to the pointer solution was that
the variables went out of scope (went past the terminating '}' brace)
and were destroyed before the FLTK library got to see them and therefore
didn't render.

In this project the main.cpp created the variables s1..s4 and they stay
valid till the ending brace of main.cpp. These variables in turn are 
objects of type Smiley which are composed of 5 Shape objects. The Smiley objects
emit a message to console when they are constructed and when they are destructed.

# To Run:

``` bash
git clone git@github.com:opentechschool-zurich/cpp-co-learning.git
cd programming-principles-and-practice/13-graphics-classes/Richard/ImprovedAcidSmiley/
mkdir build
cd build
cmake ..
make
./ImprovedAcidSmiley
```
