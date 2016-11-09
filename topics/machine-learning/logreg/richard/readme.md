### Linear Regression

This project uses a couple of 2D points to figure out the line that best
fits through them which is known as Linear Regression. This is done with
the Mlpack library which uses Armadillo which has some Fortran in it.

I cloned the wxWidgets GUI that I built for the ObserverGUI project and modified
it for this project.

The GUI was created with [wxFormBuilder](https://sourceforge.net/projects/wxformbuilder/)
which creates the C++ MyFrame_generated.ccp and MyFrame_generated.h files.
The wxFormBuilder model is stored in the file src-formbuilder/MyGui.fbp
I have not yet figured out how to thel wxFormBuilder about the wxChartPanel. I
subclassed the wxPanel to a wxChartPanel but there are still tweaks that need
to be made to the constructor and includes for the generated files to compile.
That is why there is a copy of the generated files in the main src directory.
