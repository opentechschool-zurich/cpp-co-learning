#include "XYChart.h"
#include <iostream>

DynamicDemoDataset::DynamicDemoDataset() {
    //m_updater = new DynamicDemoDatasetUpdater(this);
}

DynamicDemoDataset::~DynamicDemoDataset() {
    //wxDELETE(m_updater);
}


Chart * XYChart::Create() {
    // first step: create plot
    XYPlot *plot = new XYPlot();

    // create dynamic dataset
    m_dataset = new DynamicDemoDataset();

    // set line renderer to it
    m_dataset->SetRenderer(new XYLineStepRenderer());

    // add our dataset to plot
    plot->AddDataset(m_dataset);

    // create left and bottom number axes
    NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
    NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

    // we setup window
    //bottomAxis->SetWindow(0, 10);
    //bottomAxis->SetUseWindow(true);

    // add axes to plot
    plot->AddAxis(leftAxis);
    plot->AddAxis(bottomAxis);

    // link axes and dataset
    plot->LinkDataVerticalAxis(0, 0);
    plot->LinkDataHorizontalAxis(0, 0);

    // and finally create chart
    Chart *chart = new Chart(plot, wxT("XY Demo 5 - dynamic"));

    // set axis as scrolled, so chart panel can scroll its window.
    //chart->SetScrolledAxis(bottomAxis);
    return chart;
}

void XYChart::newPriceCallback(float price) {
    m_dataset->Add(price);
}