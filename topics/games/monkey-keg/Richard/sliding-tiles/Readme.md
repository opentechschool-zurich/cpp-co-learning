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

![Solver1](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/solver1.png)
![Solver2](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/solver2.png)
![Solver3](http://opentechschool-zurich.github.io/cpp-co-learning/topics/games/monkey-keg/Richard/sliding-tiles/solver3.png)





## Copyright information
The Font was taken from http://www.1001freefonts.com/changa_one.fontIt is in the public domain and licenced under OFL and GPL
Designer was Eduardo Tunni http://www.1001freefonts.com/search.php?d=1&q=Eduardo+Tunni


The tiles were drawn by Richard Eigenmann. They are ugly and you will be criticized if you reuse them.
