# A Duck with behavior injection 

In the "original" `duck/` implementation, each specific duck class has creates an object.

With this "injection" it's the `Duck` base class that manages the storage of the behavior.

## The copy constructor

Since the quacking behavior is a pointer, we need a (deep) copy constructor.

For the copy constructor -- the behavior being abstract -- each QuackBehavior needs a clone() method that returns a copy of the actual type.
