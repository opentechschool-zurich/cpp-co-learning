# C++ libui histogramm

C++ version of the [libui](https://github.com/andlabs/libui) `histogramm.c` example.

This version encapsulates the global variables in class.

## `main-single-class.cpp`

The whole program is placed in one single class:

- Clobal variables and static functions are replaces by class paramers and methods.
- Introduction of a templates based solution for connecting capturing lambdas and class methods with `C` callbacks.

It works correctly.

## `main.cpp`

- Encapsulate the code in task specific classes:
  - Histogram
  - Window
  - ToolboxWidget
  - HistogramWidget
  - Color
- create a callback mechanisme for `onChange`s based on vectors of capturing lambdas.

It does compile but crashes when changing the spinbox' value.  
The reason is the fact that in `Window` the two widgets are not defined as class parameters.  
And it's not easy to define them as class parameters, because they then have to the initialized before the cunstructur has run.  
And some items cannot be Gtk environment has been initialized.

We have to check the separation in classes and what is initialized where.
