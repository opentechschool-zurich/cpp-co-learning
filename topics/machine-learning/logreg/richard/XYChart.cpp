#include "XYChart.h"
#include <wx/xy/xydynamicdataset.h>
#include <mlpack/methods/linear_regression/linear_regression.hpp>
#include <armadillo>

using namespace mlpack::regression;

typedef std::vector<double> stdvec;
typedef std::vector< std::vector<double> > stdvecvec;

Chart * XYChart::Create() {
    XYPlot *plot = new XYPlot();

    // Create an Armadillo matrix and load it from a file
    arma::mat matrix;
    mlpack::data::Load("../dataset.csv", matrix);
    // Convert the Armadillo matrix to a XYDynamicSerie for wxFreeChart
    XYDynamicSerie *serie = new XYDynamicSerie();
    for ( unsigned int i = 0; i < matrix.n_cols; ++i) {
        serie->AddXY(matrix.at(0,i), matrix.at(1,i));
    }
    arma::mat x_row = matrix.row(0);
    double x_min = x_row.min();
    double x_max = x_row.max();

    // ask Mlpack to figure out the Linear Regression
    arma::vec y_row;
    y_row = vectorise(matrix.row(1));
    LinearRegression lr(x_row, y_row);

    // ask Mlpack to figure out the corresponding y values for the
    // low and high x points.
    arma::mat points {x_min, x_max};
    arma::vec predictions;
    lr.Predict(points, predictions);

    XYDynamicSerie *linear_regression_serie = new XYDynamicSerie();
    linear_regression_serie->AddXY(x_min, predictions[0]);
    linear_regression_serie->AddXY(x_max, predictions[1]);

    XYDynamicDataset *dataset = new XYDynamicDataset();
    dataset->AddSerie(serie);
    dataset->AddSerie(linear_regression_serie);

    // set line renderer with symbols enabled and lines enabled
    XYLineRenderer *renderer = new XYLineRenderer(true, true);
    // we can't pick different renderers per series but we can set the lines
    // to wxTRANSPARENT for series 0
    renderer->SetSeriePen(0, wxThePenList->FindOrCreatePen(*wxBLACK, 1, wxTRANSPARENT));
    renderer->SetSeriePen(1, wxThePenList->FindOrCreatePen(*wxBLUE, 4, wxSOLID));
    dataset->SetRenderer(renderer);

    // add our dataset to plot
    plot->AddDataset(dataset);

    // create left and bottom number axes
    NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
    NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

    // optional: set axis titles
	leftAxis->SetTitle(wxT("X"));
	bottomAxis->SetTitle(wxT("Y"));

    // add axes to plot
    plot->AddAxis(leftAxis);
    plot->AddAxis(bottomAxis);

    // link axes and dataset
    plot->LinkDataVerticalAxis(0, 0);
    plot->LinkDataHorizontalAxis(0, 0);

    // and finally create chart
    Chart *chart = new Chart(plot, wxT("Linear Regression"));

    // set axis as scrolled, so chart panel can scroll its window.
    //chart->SetScrolledAxis(bottomAxis);
    return chart;
}
