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

In order to see only the math in action this project complies a linear_regression_cli
program which shows only the math. Here is the source code of linear_regression_cli.cpp:
```cpp
#include <iostream>
#include <mlpack/methods/linear_regression/linear_regression.hpp>
#include <armadillo>

using std::cout;
using std::endl;
using namespace mlpack::regression;

int main() {
    // Create an Armadillo matrix and load it from a file
    arma::mat matrix;
    mlpack::data::Load("../dataset.csv", matrix);
    cout << "The loaded dataset.csv looks like this in the Armdillo matrix:" << endl;
    matrix.print();

    arma::mat x_row = matrix.row(0);
    double x_min = x_row.min();
    double x_max = x_row.max();
    cout << "The smallest x value is: " << x_min << endl;
    cout << "The largest x value is: " << x_max << endl;

    // ask Mlpack to figure out the Linear Regression
    arma::vec y_row;
    y_row = vectorise(matrix.row(1));
    LinearRegression lr(x_row, y_row);

    // ask Mlpack to figure out the corresponding y values for the
    // low and high x points.
    arma::mat points {x_min, x_max};
    arma::vec predictions;
    lr.Predict(points, predictions);

    cout << "The prediction for x=" << x_min << " is y=" << predictions[0] << endl;
    cout << "The prediction for x=" << x_max << " is y=" << predictions[1] << endl;

    cout << "Linear Regression Lambda is: " << lr.Lambda() << endl;

    // Get the parameters, or coefficients.
    arma::vec parameters = lr.Parameters();
    cout << "parameters (coefficients): ";
    for ( auto p : parameters ) {
        cout << p << " ";
    }
    cout << endl;

    return 0;
}
```

###Output:
```
The loaded dataset.csv looks like this in the Armdillo matrix:
   1.4200e+01   1.6400e+01   1.1900e+01   1.5200e+01   1.8500e+01   2.2100e+01   1.9400e+01   2.5100e+01   2.3400e+01   1.8100e+01   2.2600e+01   1.7200e+01
   2.1500e+02   3.2500e+02   1.8500e+02   3.3200e+02   4.0600e+02   5.2200e+02   4.1200e+02   6.1400e+02   5.4400e+02   4.2100e+02   4.4500e+02   4.0800e+02
The smallest x value is: 11.9
The largest x value is: 25.1
The prediction for x=11.9 is y=198.571
The prediction for x=25.1 is y=595.731
Linear Regression Lambda is: 0
parameters (coefficients): -159.474 30.0879
```


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
