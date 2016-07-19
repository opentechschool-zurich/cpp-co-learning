### ObserverGUI

This project revolves around the Observer Pattern. We have a PricePublisher
which has some prices of the Apple share from 2016. It pushes a new prices every
400ms to the registered observers.

The GUI was created with [wxFormBuilder](https://sourceforge.net/projects/wxformbuilder/) which creates the C++ MyFrame_generated.ccp
and MyFrame_generated.h files. The wxFormBuilder data is stored in the src-formbuilder
directory as ObserverGUI.fbp

These pre-generated files then need to be extended by classes that have the
actual application logic (MVC). This is done in MyFrame.cpp and MyFrame.h

By clicking buttons in the GUI a PriceObserver can be registered with the
PricePublisher. The idea is to have a class that inherits from PriceObserver
and overrides the virtual method newPriceCallback(float price)
This is called every time the PricePublisher wants to publish a new price.
The TextCtrlPriceObserver receives the new prices and updates the text control that
shows the price in the GUI. Likewise a HighPriceObserver and LowPriceObserver can
be turned on that update the GUI when a new high or new low price is detected.
The AvgPriceObserver calculates a current average price.

To take this to the next level the project links to the wxFreeChart library
and connects to an XYChart that draws it's line based on data in a vector. The
vector is connected as a PriceObserver and also gets the prices published by the
PricePublisher.

## Doxygen documentation

http://opentechschool-zurich.github.io/cpp-co-learning/topics/wxwidgets/Richard/ObserverGUI/build/doxygen/html/index.html

## Compiling notes

First you need to have the wxWidgets development libraries installed. I used a 3.0.2 version.

Next you need to download, compile and install wxFreeChart.
https://github.com/IGNF/wxfreechart Is a version with cmake. Run a "make install" to
install the library to the correct place.

Then do the usual cmake .. && make

Start the ObserverGUI executable
