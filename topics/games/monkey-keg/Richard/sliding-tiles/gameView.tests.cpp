#include "gameView.h"
#include <gmock/gmock.h>
#include "game.h"

using namespace SlidingTiles;

TEST(GameView, ObjectCreation) {
    SlidingTiles::GameView gameView{};
}

TEST(GameView, renderMethod) {
    std::string game2[GameBoard::boardSize][GameBoard::boardSize]{
        " ", " ", " ", " ",
        " ", " ", " ", " ",
        " ", " ", "-", " ",
        //" "," ","├",""
        " ", " ", "├", "┐"
    };

    //GameBoardSingleton::getInstance().loadGame(game2);
    GameBoard gameBoard{};
    gameBoard.loadGame(game2);
    SlidingTiles::GameView gameView{};
    gameView.setGameBoard(&gameBoard);


    gameView.render();
}
