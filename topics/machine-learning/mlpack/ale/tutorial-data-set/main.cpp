#include <mlpack/core.hpp>

using namespace mlpack;

int main(int argc, char** argv)
{
    CLI::ParseCommandLine(argc, argv);

    arma::mat dataset;
    mlpack::data::Load("../dataset.csv", dataset);

    arma::mat randomDataset = arma::randu<arma::mat>(3, 10);
    mlpack::data::Save("dataset.csv", randomDataset);

    mlpack::data::DatasetInfo info;
    arma::mat categoricalDataset;
    mlpack::data::Load("../categorical.csv", categoricalDataset, info);

	for (size_t i = 0; i < info.Dimensionality(); ++i)
	{
	  // The Type() function returns whether or not the data is numeric or
	  // categorical.
	  if (info.Type(i) != mlpack::data::Datatype::categorical)
		categoricalDataset.row(i) += 1.0;
	}
	// Save the modified dataset using the same DatasetInfo.
	// mlpack::data::Save("dataset-new.tsv", dataset, info);
	mlpack::data::Save("dataset-new.csv", categoricalDataset);
}
