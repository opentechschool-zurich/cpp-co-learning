# Use a class method as a function pointer

It's not possible to pass capturing lambdas and otherwise not trivial to pass to a (non static) class method to a C function pointer.

[Anne van Rossum](http://stackoverflow.com/users/666057/anne-van-rossum) presents on Stackoverflow a template based solution that seem to make it possible to pass to C code a method that accesses its object context:

<http://stackoverflow.com/questions/1000663/using-a-c-class-member-function-as-a-c-callback-function>

