# Injecting a behavior

The behavior D is injected in the base class A when the B object is created.

This allows to restrict the memory management in the base class.

This implementation misses a copy constructor. See the `duck-injection` project for a more complete implementation.
