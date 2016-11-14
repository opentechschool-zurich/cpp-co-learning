# Linear Regression

This project uses a couple of 2D points to figure out the line that best
fits through them which is known as Linear Regression. This is done with
the Mlpack library which in turn uses Armadillo.

![Screenshot of a Linear Regression](http://opentechschool-zurich.github.io/cpp-co-learning/topics/machine-learning/logreg/richard/Linear_regression.png)

The points come off the file dataset.csv in this repo and are plotted on one series.
The code then asks Mlpack to figure out the Linear Regression of the points as
per the tutorial <http://mlpack.org/docs/mlpack-2.1.0/doxygen.php?doc=lrtutorial.html>
We then ask the Armadillo matrix for the leftest x value and the rightest x value.
With these we ask Mlpack's Linear Regression object to predict the corresponding y
values. Thus we have the coordinates for the starting point of the line on the left edge of the chart and the ending point at the right edge of the chart. We can constuct a second series with these two points and can have this rendered as a line.

The GUI was created with [wxFormBuilder](https://sourceforge.net/projects/wxformbuilder/)
which creates the C++ MyFrame_generated.ccp and MyFrame_generated.h files.
The wxFormBuilder model is stored in the file src-formbuilder/MyGui.fbp
The program then attaches a wxBoxSizer with the chart panel to the form.

Note that wxWidgets applications don't have a main function. The macro
IMPLEMENT_APP(MyApp) in the MyApp.cpp file sets this up automatically.

##Prerequisites

You need a lot of packages installed:

**wxFreeChart** version 1.6 Either from package repo or from the source <http://wxcode.sourceforge.net/components/freechart> or from a cmake repo: <https://github.com/richardeigenmann/wxfreechart>

**wxWidgets-devel** 3.0 or later from package repo

**Mlpack-devel** Either from package or from source <http://mlpack.org>

**armadillo-devel** from package repo (could be a dependency for Mlpack if you had a package for that)

**boost-serialization** from boost-devel (could be a dependency for Armadillo if you
have a package for that)

**Cmake**  The Cmake build environment

##Building

```bash
cd cpp-co-learning/topics/machine-learning/logreg/richard
mkdir -p build
cmake ..
make
./linear_regression
```
