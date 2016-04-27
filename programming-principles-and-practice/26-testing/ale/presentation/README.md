# 26.  Testing

The systematic search of errors that the compiler cannot catch.

- Testing code's correctness
- Regression tests
- Testing performance
- Unit testing vs System testing
- Design for testing
- Automating tests
- Testing Driven Development

## Testing code's correctness

- Non-trivial programs have bugs. Always.
- We hope that bug fixes have less (serious) bugs than the fixed code.
- Read the code, to find where the easy bugs could be.
- Look hard for bugs that can crash the program.

## Proving code correct

- Theoretically (mostly) possible.
- Too hard for the programmer / desgigner.
- There are programming languages aiming at / helping achieving correctness.

So -- as Dijkstra said -- "Testing can reveal the presence of errors, not their absence."

## Regression tests

Before fixing reported bugs, one should create a test reproducing it.

The regression test suite will be run each time the code changes (future bug fixes) and ensure that fixed bugs do not reappear.

## Unit testing

Testing units (classes, functions, ...) of code, indipendently of each other.

You can find potential weak points by reading the code, or by systematically testing the interface.

Most of the time, fixing errors at the "unit" level is easier than tracking them at system level

## System testing

Testing the system as a whole.

## Writing good tests

- Using the requirements to write tests
- Tests should not be too tight bound to the current implementation details.
- Test code should be as simple as possible.
- Prioritize _likely mistakes_ and _bad mistakes_
- Only test inside of the specification

## What to test

Extrem cases and boundary conditions:

- the emtpy set;
- small sets;
- large sets;
- sets with extreme distributions;
- sets with duplicated elements;
- set with the _interesting_ items at specific places;
- random sets.

## Design for testing

- use well-defined interfaces;
- test the assumptions in the calling code;
- minimize the dependencies and make them explicit;
- have a clear resources management strategy.

## Test driven development

- write the test (it will fail)
- write the mininimal code that satisfies the new test (it will succeed)
- eventually refactor your code (it should still succeeed)
- restart the loop

→ red → green → red → ...
