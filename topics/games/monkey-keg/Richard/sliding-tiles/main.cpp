#include "game.h"
//#include "puzzleSolver.h"

#include <random> // random_shuffle, std::default_random_engine
#include <chrono> // std::chrono::system_clock

using namespace SlidingTiles;

int main() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    Game game{};
    
    //PuzzleSolver puzzleSolver{};
    //puzzleSolver.generateGames( 10);
    
    game.run();
}
