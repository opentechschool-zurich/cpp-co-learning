#include "game.h"
#include "gameBoard.h"
#include <cmath>
#include "puzzleSolver.h"

using namespace SlidingTiles;

namespace SlidingTiles {

    Game::Game() {
        std::string game3[GameBoard::boardSize][GameBoard::boardSize]{" ", " ", "-", "┬",
            " ", " ", " ", "|",
            " ", " ", "|", " ",
            " ", " ", " ", "┻"};

        std::string game1[GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "-", "┐",
            "┣", "┐", " ", "|",
            "┌", "┘", " ", "|",
            "└", "-", "-", "┘"};

        std::string game2[GameBoard::boardSize][GameBoard::boardSize]{
            " ", " ", " ", " ",
            " ", " ", " ", " ",
            " ", " ", "-", " ",
            //" "," ","├",""
            " ", " ", "├", "┐"
        };

        std::string game4[GameBoard::boardSize][GameBoard::boardSize]{" ", " ", " ", "┬",
            " ", "|", " ", " ",
            " ", " ", " ", "┻",
            " ", " ", " ", " "};

        //GameBoardSingleton::getInstance().loadGame(game2);
        gameBoard.loadGame(game4);
        gameView.setGameBoard(&gameBoard);
    }

    void Game::update(const float & dt) {
        // send update event to all the tiles
        for (int x = 0; x < GameBoard::boardSize; ++x)
            for (int y = 0; y < GameBoard::boardSize; ++y) {
                //GameBoardSingleton::getInstance().tiles[x][y].tileView.update(dt);
                gameBoard.tiles[x][y].tileView.update(dt);
            }

        // see if there is a solution
        //std::vector<sf::Vector2i> solutionPath = GameBoardSingleton::getInstance().isSolved();
        std::vector<sf::Vector2i> solutionPath = gameBoard.isSolved();
        if (solutionPath.size() > 0) {
            //GameBoardSingleton::getInstance().setWinnerTiles( solutionPath );
            gameBoard.setWinnerTiles(solutionPath);
        } else {
            //GameBoardSingleton::getInstance().clearWinnerTiles();
            gameBoard.clearWinnerTiles();
        }
    }

    void Game::run() {
        sf::RenderWindow* window = RenderingSingleton::getInstance().getRenderWindow();
        while (window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
                else if (event.type == sf::Event::MouseButtonPressed) {
                    doMousePressed(sf::Vector2i{event.mouseButton.x, event.mouseButton.y});
                } else if (event.type == sf::Event::MouseButtonReleased) {
                    doMouseReleased(sf::Vector2i{event.mouseButton.x, event.mouseButton.y});
                } else if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 114) { //r
                        doRandomGame();
                    } else if (event.text.unicode == 112) { //p 
                        gameBoard.printGame();
                    } else
                        std::cout << "ASCII character typed: " << event.text.unicode << " --> " << static_cast<char> (event.text.unicode) << std::endl;
                }
            }

            sf::Time dt = deltaClock.restart();
            update(dt.asSeconds());
            gameView.render();
        }
    }

    void Game::doRandomGame() {
        int count{0};
        //while ( sol == 0 ) {
        do {
            gameBoard.randomGame();
            SlidingTiles::MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
            rootNode.endingBoard = gameBoard.serialiseGame();
            //std::cout << rootNode.toString() << "\n";
            PuzzleSolver puzzleSolver;
            puzzleSolver.addPossibleMoves(rootNode, 3);

            std::cout << "trying a game: " << ++count << "\n";
            if (puzzleSolver.hasASolution(rootNode)) {
                count = -1;
            }
        } while (count > -1);
        //}
    }

    void Game::doMousePressed(const sf::Vector2i & mousePosition) {
        mousePositionPressed = mousePosition;
    }

    void Game::doMouseReleased(const sf::Vector2i & mousePosition) {
        sf::Vector2i movingTilePosition = RenderingSingleton::getInstance().findTile(mousePositionPressed);
        if (movingTilePosition.x == -1 || movingTilePosition.y == -1)
            return; // out of grid
        int deltaX = mousePosition.x - mousePositionPressed.x;
        int deltaY = mousePosition.y - mousePositionPressed.y;
        if (abs(deltaX) > 2 || abs(deltaY) > 2) {
            SlidingTiles::Tile movingTile = gameBoard.tiles[movingTilePosition.x][movingTilePosition.y];
            if (abs(deltaX) > abs(deltaY)) {
                // horizontal movement
                sf::Vector2i newPosition = sf::Vector2i(movingTilePosition.x + copysign(1, deltaX), movingTilePosition.y);
                if (deltaX > 0) {
                    gameBoard.slideTile(Move{movingTilePosition, Direction::GoRight});
                } else {
                    gameBoard.slideTile(Move{movingTilePosition, Direction::GoLeft});
                }
            } else {
                // vertical movement
                sf::Vector2i newPosition = sf::Vector2i(movingTilePosition.x, movingTilePosition.y + copysign(1, deltaY));
                //gameBoard.slideTile(movingTilePosition, newPosition);
                if (deltaY > 0) {
                    gameBoard.slideTile(Move{movingTilePosition, Direction::GoDown});
                } else {
                    gameBoard.slideTile(Move{movingTilePosition, Direction::GoUp});
                }

            }
        }
    }

}
