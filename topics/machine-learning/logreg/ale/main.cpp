#include <iostream>
#include <mlpack/core.hpp>
#include <mlpack/methods/logistic_regression/logistic_regression.hpp>
#include <mlpack/prereqs.hpp>

using namespace mlpack;

int main(int argc, char** argv)
{
    CLI::ParseCommandLine(argc, argv);

    arma::mat dataset;
    mlpack::data::Load("../train.csv", dataset);

    // arma::uvec nonzeros = arma::find(dataset.row(1) == 0);
    arma::uvec nonzeros = arma::find(dataset.row(1));

    arma::mat datasetClean = dataset.cols(nonzeros);
    // std::cout << datasetClean << std::endl;

    arma::Row<size_t> Y = arma::conv_to< arma::Row<size_t> >::from(datasetClean.row(0));
    arma::Mat<double> X = datasetClean.row(1);

    // mlpack::regression::LogisticRegression<> results{2};
    // results.Train(X, Y);

    mlpack::regression::LogisticRegression<> results{X, Y};

    std::cout << results.Parameters() << std::endl;

    double decisionBoundary{0.4}; // there are too many dead people: we have to sink the threshold

    arma::Mat<double> A{2.5};
    std::cout << results.Classify(A, decisionBoundary) << std::endl;

    arma::Mat<double> B{80};
    std::cout << results.Classify(B, decisionBoundary) << std::endl;

    arma::Row<double> C{20};
    std::cout << results.Classify(C, decisionBoundary) << std::endl;

    // mlpack::regression::LogisticRegression<arma::mat> reg_results(X,Y);
    // mlpack::regression::LogisticRegression<arma::mat> reg_results(datasetClean);

    // BTW the type for Y should be something different like Row<size_t> but I still have not managed how to transform the Row<double> we get into it..

    // auto results = mlpack::regression::LogisticRegression<arma::mat>::LogisticRegression(X, Y);


}
