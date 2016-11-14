### Linear Regression

This project uses a couple of 2D points to figure out the line that best
fits through them which is known as Linear Regression. This is done with
the Mlpack library which uses Armadillo which has some Fortran in it.

![Screenshot of a Linear Regression](http://opentechschool-zurich.github.io/cpp-co-learning/topics/machine-learning/logreg/richard/Linear_regression.png)

The points come off the file dataset.csv in this repo and are plotted on one series.
The code then asks Mlpack to figure out the Linear Regression of the points as
per the tutorial [http://mlpack.org/docs/mlpack-2.1.0/doxygen.php?doc=lrtutorial.html]
We then ask the Armadillo matrix for the leftest x value and the rightest x value.
With these we ask Mlpack's Linear Regression object to predict the corresponding y
values. Thus we have the coordinates for the line on the left edge of the chart
and the right edge of the chart. We can constuct a second series with these two
points and can have this rendered as a line.


I cloned the wxWidgets GUI that I built for the ObserverGUI project and modified
it for this project.

The GUI was created with [wxFormBuilder](https://sourceforge.net/projects/wxformbuilder/)
which creates the C++ MyFrame_generated.ccp and MyFrame_generated.h files.
The wxFormBuilder model is stored in the file src-formbuilder/MyGui.fbp
I have not yet figured out how to thel wxFormBuilder about the wxChartPanel. I
subclassed the wxPanel to a wxChartPanel but there are still tweaks that need
to be made to the constructor and includes for the generated files to compile.
That is why there is a copy of the generated files in the main src directory.

##Building

#Prerequisites

You need a lot of packages installed:
**wxFreeChart** version 1.6 Either from package repo or from the source [http://wxcode.sourceforge.net/components/freechart/] or from a cmake repo: [
https://github.com/richardeigenmann/wxfreechart]

**wxWidgets-devel** 3.0 or later from package repo

**armadillo-devel** from package repo

**Mlpack-devel** Either from package or from source [http://mlpack.org/]

**Cmake**  The Cmake build environment

#Building

```bash
cd cpp-co-learning/topics/machine-learning/logreg/richard
mkdir -p build
cmake ..
make
./linear_regression
```
