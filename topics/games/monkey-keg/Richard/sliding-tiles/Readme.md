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
cmake ..
make
./sliding-tiles
```

## Build and run on Visual Studio 2017
It can be done!
You need to install
* CMake
* Python
* SFML
* Visual Studio 2017

Edit the CMakeLists.txt file and edit the line where the SFML root
directory is on your machine. Unfortunately this doesn't actually have any real effect but it should.

Then open the CMake GUI. It wants to know "Where is the source code:". Give it the sliding-tiles root directory.
It also wants to know the build directory. Create a build subdirectory and point the gui at that.

Click the Configure button. If you do this the first time it will ask you for the generator. Pick the Visual Sutdio 15 2017 Win64 generator. Be sure to pick a 64 bit generator if you downloaded the 64 bit SFML library! You could end up with an unhelpful linker error saying it doesn't like x86 in a x64 project.

This would have generated a sliding-tiles.sln file along with lots of other stuff in the sliding-tiles/build directory. Open this with Visual Studio 2017.

In Visual Studio you next need to open up the Solution Explorer. If it is not showing pick it from the View > Solution Explorer menu.

The Solution Explorer shows a bewildering amount of build targets. In order to build the game we need to tell the sliding-tiles target where to find the SFML stuff. Right-click on the sliding-tiles target (this is NOT the "Solution 'sliding-tiles' (10 projects)" root note - it's is one level down!!). In the pop-up menu open "Properties".

Unfold the "C/C++" node and click on "General". First line on the right side is "Additional Include Directories" where the directory from the CMakeLists.txt file should have been included. Click on the line and a little drop-down icon appears at the far right. Click this and a pop down menu appears. Click on &lt;Edit...&gt; to open a dialog window. In the white box at the top of the dialog click on the empty space. This "highlights" the line and a "three dot icon" appears on the right hand side. Click this and in the filechooser dialog pick the Include subdirectory from where you installed SFML. Click OK to go back to the Properties page.

The next step is to tell the Linker where to find the lib files. Using the same mystery navigation click on the "Linker" key on the left side list. Pick "General" and click on "Additional Library Directories". Into that field's edit dialog add the lib directory from your SFML installation.

Next click on "Input" in the Liker section. The top line is "Additional Dependencies". This list is already pre-populated. add the following items to it:
* sfml-window-d.lib
* sfml-system-d.lib
* opengl32.lib
* freetype.lib
* jpeg.lib

On the top right of the dialog is a button for the Configuration Manager. Open this and untick the unit-tests.

Now you can build the software! Click Build > Build Solution from the menu. (Be sure not to have the game open or the build will fail to overwrite the exe file "LINK1168: Cannot open ... for writing".) Hopefully it builds with no error. The SFML tutorial shows how to set this up too: http://www.sfml-dev.org/tutorials/2.4/start-vc.php

You are not done yet. You should now have a sliding-tiles.exe file in the sliding-tiles/build/Debug directory. If you open it, it will complain about missing DLL files. You need to copy all the .dll files in the SFML/bin directory to this directory. Also copy the sliding-tiles/asses subdirectory to this sliding-tiles/build/Debug directory. But now the game should start up!


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
The Font was taken from http://www.1001freefonts.com/changa_one.fontIt is in the public domain and licenced under OFL and GPL
Designer was Eduardo Tunni http://www.1001freefonts.com/search.php?d=1&q=Eduardo+Tunni


The tiles were drawn by Richard Eigenmann. My artistic skills are gradually improving...
