#include <iostream>
#include <mlpack/core.hpp>
#include <mlpack/methods/logistic_regression/logistic_regression.hpp>

using namespace std;
using namespace mlpack;

int main(int argc, char** argv)
{
    arma::mat dataset; // This is actually the matrix store


    string datafile = "train_onlyage.csv";
    if (data::Load(datafile, dataset)) {
        //Log::cout << datafile << " row 1 is:" << std::endl;
        //Log::cout << dataset.row(1);

        // get the indexes where there are no zeros
        arma::uvec indexes = arma::find(dataset.row(1));

        arma::mat cleandataset = dataset.cols(indexes);


        arma::mat predictors = cleandataset.row(1);
        arma::Row<size_t> results = arma::conv_to< arma::Row<size_t> >::from(cleandataset.row(0));
//        auto reg = regression::LogisticRegression<>(
//                    predictors,
//                    results
//                   );

        regression::LogisticRegression<arma::mat> reg {predictors, results};

        cout << "With logistic regression training we'vwe got these parameters:" << endl << reg.Parameters();


        int age = 54;
        arma::vec testLifeOf {age};
        //arma::Row<size_t> deadOrAlives{3};
        //testLifes(0) = 5;
        cout << "The guy with age " << age << " is: " << reg.Classify(testLifeOf) << endl;


    }


}

