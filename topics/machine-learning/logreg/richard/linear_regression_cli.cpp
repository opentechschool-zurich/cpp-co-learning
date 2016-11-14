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
