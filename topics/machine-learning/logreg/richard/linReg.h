#pragma once
#include <mlpack/methods/linear_regression/linear_regression.hpp>

using std::cout;
using namespace mlpack::regression;

void doLinearRegression() {
  arma::mat dataset;
  mlpack::data::Load("../dataset.csv", dataset);
  cout << "The dataset values:\n";
  dataset.print();

  arma::mat x = dataset.row(0);
  cout << "The x values:\n";
  x.print();

  arma::vec y;
  y = vectorise(dataset.row(1));
  cout << "The vectorised y values:\n";
  y.print();

  LinearRegression lr(x, y);
  arma::vec parameters = lr.Parameters();
  cout << "The Linear Regression parameters:\n";
  parameters.print();

  arma::mat points;
  mlpack::data::Load("../predict.csv", points);
  cout << "The points to predict:\n";
  points.print();

  arma::vec predictions;
  lr.Predict(points, predictions);
  cout << "The predictions:\n";
  predictions.print();
}
