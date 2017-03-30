# Sliding Tiles

## Screenshot
![Screenshot](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/Screenshot.png)

## Description:
This program creates a window and places tiles in a grid.
The tiles can be slid around by dragging the mouse.
When the start and end tile match up in a path you win.


## Build and run
```bash
mkdir -p build
cd build
export CXX=/usr/bin/g++-6 # only if you have an old compiler and need to override the default to a modern one
cmake ..
make
./sliding-tiles
```

## Build and run on Visual Studio 2017
This is a CMake project. That means that we let CMake create the solution files in the build directory from the CMakeLists.txt file

You need to install
* [CMake](https://cmake.org/download)
* [Python 2.x, not 3.x](https://www.python.org/downloads/release)
* [SFML](https://www.sfml-dev.org/download.php)
* [Visual Studio 2017](https://www.visualstudio.com/downloads)

On windows there is no standard place that SFML goes. So you need to tell CMake in the CMakeLists.txt file where it is. Edit this file and adjust the SFML_ROOT delcaration on line 6.

Then open the CMake GUI. It wants to know "Where is the source code:". Give it the sliding-tiles root directory.
It also wants to know the build directory. Create a build subdirectory and point the gui at that.

Click the Configure button. If you do this the first time it will ask you for the generator. Pick the Visual Sutdio 15 2017 Win64 generator. Be sure to pick a 64 bit generator if you downloaded the 64 bit SFML library! You could end up with an unhelpful linker error saying it doesn't like x86 in a x64 project.

![CMakeScreenshot](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/cmake.png)

Then click Generate to create the sliding-tiles.sln solution file along with lots of other stuff in the sliding-tiles/build directory. Open this with Visual Studio 2017 by clicking "Open Project".

To build the software click Build > Build Solution from the menu. (Be sure not to have the game open or the build will fail to overwrite the exe file "LINK1168: Cannot open ... for writing".)

You should now have a sliding-tiles.exe file in the sliding-tiles/build/Debug directory. You can run it from that directory or start it with the debugger (green triangle or F5).

To run the unit tests. Right click in the Solution Explorer on "unit-tests" and pick "Set as StartUp project". Now you can run them without the debugger by pressing Ctrl-F5 or perhaps with the debugger by pressing F5 (but the terminal window closes on you then).

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
## Notable Points:

### Segfault on textures
What's the difference between

```c++
sf::Texture & getTexture(const TileType & tileType) {
    return texturesMap[tileType];
};
```

And this?
```c++
sf::Texture getTexture(const TileType & tileType) {
    return texturesMap[tileType];
};
```

And what kind of difference could it possibly make to this code?
```c++
void TileView::render() {
    sf::Sprite sprite;
    sprite.setTexture(TexturesSingleton::getInstance().getTexture(tileType));
    sprite.setPosition(renderPosition.x, renderPosition.y);
    RenderingSingleton::getInstance().getRenderWindow()->draw(sprite);
}
```

Turns out a huge difference: The difference is that easy-to-overlook little
ampersand in the return value declaration of the getTexture method.

Without the
ampersand the method returns a copy of the texture from the texturesMap (which
exists only once in the singleton). Whilst perhaps not optimally efficient
why should this be a problem? After all, the texture exists till the closing
brace in the render method. A few hundred segfaults later my suspicion is that
the draw method goes off into some asynchronous heaven and by the time it gets
round to picking up the texture the closing brace has come along and wiped the
texture off the stack and we get a segfault.

By adding the ampersand the getTexture method returns a reference to the texture
in the map. This is also on the stack but the texturesMap is a long living object
in the singleton so it does not go away and any delayed draw can happily access
it.


### Searching for a solution - A breadth first search!

For a human it is easy to see how to solve this puzzle:

![Solver1](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/solver1.png)
![Solver2](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/solver2.png)
![Solver3](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/solver3.png)

To solve programatically we can take a brute-force approach: Start with the puzzle
and figure out all possible moves that can be made by the tiles. In this puzzle
there is only one tile that can move (start and end tiles are fixed). It can
move in 4 directions.

If the tile moves to the right on the next move it can still move 3 ways. Note that
moving back is not desirable so we will only consider 3 potential moves.

If the tile moves to the right once more then it has no more future moves. In this
situation that is OK because the puzzle has been solved.

This making-a-move and then having multiple next moves can be expressed as a tree:

![Level1](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/Level1.png)

We can visit each node and see if there are new moves (excluding the go back move):

![Level2](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/Level2.png)

As we go n-deep the number of nodes increases. I'm sure there is some optimisation
that could be applied to prevent tiles moving round in circles. But we are on the
brute-force approach here...

![Level4](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/doc/Level4.png)

Which path is the fastest one that leads to a solved puzzle? Enter the breadth-first
search:

![Breadth-First-Search](https://upload.wikimedia.org/wikipedia/commons/5/5d/Breadth-First-Search-Algorithm.gif)

(From Wikipedia: https://en.wikipedia.org/wiki/Breadth-first_search )

Here is "my" code to find the shortest solution path:
```c++
bool PuzzleSolver::hasASolution(const MoveNode & node) {
    // inspired by https://gist.github.com/douglas-vaz/5072998
    std::queue<MoveNode> Q;
    Q.push(node);
    while (!Q.empty()) {
        MoveNode t = Q.front();
        Q.pop();
        gameBoard.loadGame(t.endingBoard);
        if (gameBoard.isSolved().size() > 0) {
            return true;
        };
        for (int i = 0; i < t.possibleMoves.size(); ++i) {
            Q.push(t.possibleMoves[i]);
        }
    }
    return false;
}
```

I was impressed with the queue approach which avoids a recursive call. The method
places the root node on the queue and then reads nodes off the front of the queue.
If the endboard of the move isn't a solved puzzle the method looks for the
child moves and adds them at the end of the queue. This way first all the level 1
nodes are visited before the level 2 nodes are checked and so on.


## Copyright information
Designer was Eduardo Tunni http://www.1001freefonts.com/search.php?d=1&q=Eduardo+Tunni
The source includes a copy of JSON for Modern C++ from Niels Lohmann [GitHub](https://github.com/nlohmann/json) This is MIT licenced.
Trophy Clipart from http://www.clipartbest.com/clipart-aieonzEzT
The buttons were created by https://dabuttonfactory.com/
The Raleway font is a Google Font with Open Font License: https://fonts.google.com/specimen/Raleway

The tiles were drawn by Richard Eigenmann. My artistic skills are gradually improving...