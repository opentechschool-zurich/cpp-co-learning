# Sliding Tiles

## Screenshot
![Screenshot](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/Screenshot.png)

## Description:
This program creates a window and places tiles in a grid.
The tiles can be slid around by dragging the mouse.
When the start and end tile match up in a path you win.


## Build and run
```bash
mkdir -p build
cd build
cmake ..
make
./sliding-tiles
```

## Doxygen Documentation
```bash
mkdir -p build
cd build
doxygen ../Doxyfile
```

Then open the file in html/index.html in the browser


## Testing
```bash
mkdir -p build
cd build
cmake ..
make
make test
# or
./unit-tests
```

## Code Coverage
To generate code coverage reports from the unit tests run the below steps.
The CodeCoverage.cmake file used gcov from the gcc installation and lcov
which has to be installed separately to generate an html coverage report.

```bash
mkdir -p build
cd build
cmake ..
make
make sliding-tiles_coverage
# open the file coverage/index.html with a browser
```

## Copyright information
The Font was taken from http://www.1001freefonts.com/changa_one.fontIt is in the public domain and licenced under OFL and GPL
Designer was Eduardo Tunni http://www.1001freefonts.com/search.php?d=1&q=Eduardo+Tunni


The tiles were drawn by Richard Eigenmann. They are ugly and you will be criticized if you reuse them.
