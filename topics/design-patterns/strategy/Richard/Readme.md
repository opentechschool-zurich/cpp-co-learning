# Strategy Pattern

From Wikipedia:

In computer programming, the strategy pattern (also known as the policy pattern) is a software design pattern that enables an algorithm's behavior to be selected at runtime. The strategy pattern

* defines a family of algorithms,
* encapsulates each algorithm, and
* makes the algorithms interchangeable within that family.

Strategy lets the algorithm vary independently from clients that use it. Strategy is one of the patterns included in the influential book Design Patterns by Gamma et al. that popularized the concept of using patterns to describe software design.

<https://en.wikipedia.org/wiki/Strategy_pattern>


## Discussion

In this sample program we have an abstract class Duck that forces inheriting classes
to override the virtual functions display(). It is expected that the inheriting classes
must supply the flymode in the constructor.


## Abstract Classes can't be added to containers

The below two lines seem reasonable to a Java programmer
but C++ is not Java. The answer lies in the fact that Duck
is an abstract class. The extending subclasses may have more
fields and functions and therefore the size of the ultimate
object is not known. So the compiler can't figure out how 
much memory to reserve per duck and therefore it is not allowed.
Instead we can create new ducks and add pointers to the ducks to
the vector.

<http://stackoverflow.com/questions/2160920/why-cant-we-declare-a-stdvectorabstractclass>

```c++
std::vector<Duck> ducks;
ducks.push_back(duck1);
```

