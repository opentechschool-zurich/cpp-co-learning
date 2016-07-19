# FizzBuzz with try/catch

This exercise implements the classic FizzBuzz algorithm with 
try and catch exceptions.

The idea is that we have 3 classes one for Fizz (numbers dividable by 3),
one for Buzz (numbers dividable by 5) and FizzBuzz (numbers dividable 
by 3 and by 5). 

The main program iterates from 1 to 20 and checks whether the number
is dividable by 3, 5 or both. If one of the special numbers is 
detected an exception is thrown. Or rather an object is created of type
Fizz, Buzz or FizzBuzz and this object is thrown. The catch statements
then catch a particular type of object and do something special with 
it like printing the value stored in the object.