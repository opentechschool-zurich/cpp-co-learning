#include<iostream>
#include<mlpack/core.hpp>
#include<mlpack/methods/logistic_regression/logistic_regression.hpp>
#include<mlpack/prereqs.hpp>

using std::cout; 
using std::endl; 

using namespace mlpack;

int main()
{

  arma::mat mymatrix;
  mlpack::data::Load("../train_mod.csv", mymatrix); 

  // cout << "Hello" << endl
  //      << mymatrix << endl; 
 
  // cout << "Age" << endl
  //      << arma::find(mymatrix.row(1)) << endl;

  arma::uvec myidx = arma::find(mymatrix.row(1)); 
  
  arma::mat cleanmat = mymatrix.cols(myidx);

  cout << "Cleanmat: " << endl << cleanmat << endl; 

  arma::mat Y = cleanmat.row(0);
  arma::mat X = cleanmat.row(1);

  // regression::LogisticRegression<arma::mat> reg_results = regression::LogisticRegression<arma::mat>::LogisticRegression(2);

  regression::LogisticRegression<arma::mat> reg_results {2};
  
  reg_results.Train(X, Y);
  

 

  return 0; 
}
