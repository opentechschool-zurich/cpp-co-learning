#include<iostream>
#include<mlpack/core.hpp>
#include<mlpack/methods/logistic_regression/logistic_regression.hpp>
#include<mlpack/prereqs.hpp>

// usr/local/include - self compiled 
// usr/include - deb packages 

using std::cout; 
using std::endl; 

using namespace mlpack::regression;

int main()
{

  arma::mat mymatrix;
  mlpack::data::Load("../train_mod.csv", mymatrix); 
 
  arma::uvec myidx = arma::find(mymatrix.row(1)); 
  
  arma::mat cleanmat = mymatrix.cols(myidx);

  arma::mat Y = cleanmat.row(0);
  arma::mat X = cleanmat.row(1);
  arma::Row<size_t> Yvec = arma::conv_to< arma::Row<size_t> >::from(Y);
  
  LogisticRegression<arma::mat> myresults{X, Yvec};
  
  cout << myresults.Parameters() << endl; 

  arma::vec newpoint{60.0}; 
  size_t clres = myresults.Classify(newpoint);

  cout << "New point" << newpoint << endl
       << "Classification" << clres << endl;
  
  return 0; 
}
