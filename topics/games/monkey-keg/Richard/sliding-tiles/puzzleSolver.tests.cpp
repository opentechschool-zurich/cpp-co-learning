#include "puzzleSolver.h"
#include "move.h"
#include <gmock/gmock.h>

using namespace::testing;
using namespace SlidingTiles;

TEST(PuzzleSolver, possibleMovesNone) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{
        "├", "┫", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "
    };
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    //std::vector<SlidingTiles::MoveNode> possibleMoves = puzzleSolver.possibleMoves(gameBoard.serialiseGame());
    std::vector<SlidingTiles::MoveNode> possibleMoves = puzzleSolver.possibleMoves(rootNode);
    ASSERT_THAT(possibleMoves.size(), 0);
}

TEST(PuzzleSolver, possibleMovesOne) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{
        "├", "-", "┫", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "
    };
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    std::vector<MoveNode> possibleMoves = puzzleSolver.possibleMoves(rootNode);
    ASSERT_THAT(possibleMoves.size(), 1);
    MoveNode move = possibleMoves[0];
    sf::Vector2i expectedTile{1, 0};
    ASSERT_EQ(move.startPosition, expectedTile) << "Expect tile [1][0] to be a possible move but returned tile is [" << move.startPosition.x << "][" << move.startPosition.y << "] \n";
    int up{0};
    int down{0};
    int left{0};
    int right{0};
    for (auto moveNode : possibleMoves) {
        if (moveNode.direction == Direction::GoDown) {
            ++down;
        } else if (moveNode.direction == Direction::GoUp) {
            ++up;
        } else if (moveNode.direction == Direction::GoLeft) {
            ++left;
        } else if (moveNode.direction == Direction::GoRight) {
            ++right;
        }
    }
    ASSERT_EQ(up, 0);
    ASSERT_EQ(down, 1);
    ASSERT_EQ(left, 0);
    ASSERT_EQ(right, 0);
}

TEST(PuzzleSolver, possibleMovesTwo) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "┫", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " ",
        "-", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    std::vector<MoveNode> possibleMoves = puzzleSolver.possibleMoves(rootNode);
    ASSERT_THAT(possibleMoves.size(), 2);
    int up{0};
    int down{0};
    int left{0};
    int right{0};
    for (auto moveNode : possibleMoves) {
        if (moveNode.direction == Direction::GoDown) {
            ++down;
        } else if (moveNode.direction == Direction::GoUp) {
            ++up;
        } else if (moveNode.direction == Direction::GoLeft) {
            ++left;
        } else if (moveNode.direction == Direction::GoRight) {
            ++right;
        }
    }
    ASSERT_EQ(up, 1);
    ASSERT_EQ(down, 0);
    ASSERT_EQ(left, 0);
    ASSERT_EQ(right, 1);
}

TEST(PuzzleSolver, possibleMovesFour) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", " ", "┫", " ",
        " ", "-", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    std::vector<MoveNode> possibleMoves = puzzleSolver.possibleMoves(rootNode);
    ASSERT_THAT(possibleMoves.size(), 4);
    int up{0};
    int down{0};
    int left{0};
    int right{0};
    for (auto moveNode : possibleMoves) {
        if (moveNode.direction == Direction::GoDown) {
            ++down;
        } else if (moveNode.direction == Direction::GoUp) {
            ++up;
        } else if (moveNode.direction == Direction::GoLeft) {
            ++left;
        } else if (moveNode.direction == Direction::GoRight) {
            ++right;
        }
    }
    ASSERT_EQ(up, 1);
    ASSERT_EQ(down, 1);
    ASSERT_EQ(left, 1);
    ASSERT_EQ(right, 1);
}

TEST(PuzzleSolver, possibleMovesDontGoBack) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", " ", "┫", " ",
        " ", "-", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i{1, 1}, Direction::GoDown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    std::vector<MoveNode> possibleMoves = puzzleSolver.possibleMoves(rootNode);
    ASSERT_THAT(possibleMoves.size(), 3);
    int up{0};
    int down{0};
    int left{0};
    int right{0};
    for (auto moveNode : possibleMoves) {
        if (moveNode.direction == Direction::GoDown) {
            ++down;
        } else if (moveNode.direction == Direction::GoUp) {
            ++up;
        } else if (moveNode.direction == Direction::GoLeft) {
            ++left;
        } else if (moveNode.direction == Direction::GoRight) {
            ++right;
        }
    }
    ASSERT_EQ(up, 0);
    ASSERT_EQ(down, 1);
    ASSERT_EQ(left, 1);
    ASSERT_EQ(right, 1);
}


/*TEST(PuzzleSolver, possibleMovesIsSolvedIn1Move) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{
        "├", " ", "┫", " ",
        " ", "-", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "
    };
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    PuzzleSolver puzzleSolver;
    std::vector<SlidingTiles::MoveNode> possibleMoves = puzzleSolver.possibleMoves(gameBoard.serialiseGame());
    ASSERT_THAT(possibleMoves.size(), 4);
    //std::cout << possibleMoves.toString(0) << "\n";
    std::vector<Solution> solutions = puzzleSolver.solutions(gameBoard.serialiseGame(), possibleMoves);
    ASSERT_THAT(solutions.size(), 1);
    Solution s = solutions[0];
    //std::cout << "s: " << s.moves.size() << "\n";
    Move m = s.moves[0];
    m.toString();
    sf::Vector2i expectedTile{1, 1};
    ASSERT_EQ(m.startPosition, expectedTile) << "Expect tile [1][1] to move up for solution but startPosition returned is [" << m.startPosition.x << "][" << m.startPosition.y << "] \n";
}*/

/*TEST(PuzzleSolver, isSolvedIn2SingleMoves) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{" ", " ", " ", " ",
        " ", "-", " ", " ",
        "├", " ", "┫", " ",
        " ", "-", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    PuzzleSolver puzzleSolver;
    std::vector<SlidingTiles::MoveNode> possibleMoves = puzzleSolver.possibleMoves(gameBoard.serialiseGame());
    ASSERT_THAT(possibleMoves.size(), 7);
    /*std::cout << "Possible moves:\n";
    for ( MoveNode m : possibleMoves ) {
        std::cout << m.toString();
    }*/

/* std::vector<Solution> solutions = puzzleSolver.solutions(gameBoard.serialiseGame(), possibleMoves);
 ASSERT_THAT(solutions.size(), 2);
}*/

TEST(PuzzleSolver, addPossibleMoves) {
    // builds on possibleMovesOne
    std::string game [GameBoard::boardSize][GameBoard::boardSize]
    {"├", "-", "┫", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    //std::vector<MoveNode> possibleMoves = puzzleSolver.possibleMoves(rootNode);
   // ASSERT_THAT(possibleMoves.size(), 1);
    //MoveNode moveNode = possibleMoves[0];
    //sf::Vector2i expectedTile{1, 0};
    //ASSERT_EQ(moveNode.startPosition, expectedTile) << "Expect tile [1][0] to be a possible move but returned tile is [" << moveNode.startPosition.x << "][" << moveNode.startPosition.y << "] \n";
    //ASSERT_EQ(moveNode.direction, Direction::GoDown);

    puzzleSolver.addPossibleMoves(rootNode, 1);
    ASSERT_THAT(rootNode.possibleMoves.size(), 1);
    
    MoveNode moveNodeNext = rootNode.possibleMoves[0];
    std::cout << moveNodeNext.toString();
    ASSERT_THAT(moveNodeNext.possibleMoves.size(), 3);
    int up{0};
    int down{0};
    int left{0};
    int right{0};
    for (auto node : moveNodeNext) {
        std::cout << "counting node: " << node.toString();
        if (node.direction == Direction::GoDown) {
            ++down;
        } else if (node.direction == Direction::GoUp) {
            ++up;
        } else if (node.direction == Direction::GoLeft) {
            ++left;
        } else if (node.direction == Direction::GoRight) {
            ++right;
        }
    }
    ASSERT_EQ(up, 0);
    ASSERT_EQ(down, 1);
    ASSERT_EQ(left, 1);
    ASSERT_EQ(right, 1);*/
}

TEST(PuzzleSolver, addPossibleMoves3Deep) {
    // builds on addPossibleMoves which builds on possibleMovesOne
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", "-", "┫", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    //std::vector<SlidingTiles::MoveNode> possibleMoves = puzzleSolver.possibleMoves(gameBoard.serialiseGame());
    std::vector<SlidingTiles::MoveNode> possibleMoves = puzzleSolver.possibleMoves(rootNode);
    ASSERT_THAT(possibleMoves.size(), 1);
    SlidingTiles::MoveNode moveNode = possibleMoves[0];
    sf::Vector2i expectedStartTile{1, 0};
    ASSERT_EQ(moveNode.startPosition, expectedStartTile) << "Expect start tile [1][0] to be a possible move but returned tile is [" << moveNode.startPosition.x << "][" << moveNode.startPosition.y << "] \n";

    //std::cout << "\n\n---\n" << moveNode.toString() << "----\n";

    // now the addPossibleMoves stuff
    puzzleSolver.addPossibleMoves(moveNode, 3);
    //std::cout << "---\n" << moveNode.toString() << "----\n";
    ASSERT_THAT(moveNode.possibleMoves.size(), 4);


    int i = 0;
    for (; i < 4; ++i) {
        //std::cout << "moveNode.possibleMoves["<<i<<"]: " << moveNode.possibleMoves[i].toString();
        if (moveNode.possibleMoves[i].direction == Direction::GoDown) {
            break;
        }
    }

    //std::cout << "Move going down found on index: " << i << "\n";
    //std::cout << moveNode.possibleMoves[i].toString();
    MoveNode secondMove = moveNode.possibleMoves[i];
    ASSERT_THAT(secondMove.direction, Direction::GoDown);
    ASSERT_THAT(secondMove.possibleMoves.size(), 4);
}

TEST(PuzzleSolver, isSolvedIn1Move) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", " ", "┫", " ",
        " ", "-", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    puzzleSolver.addPossibleMoves(rootNode, 3);
    ASSERT_TRUE(puzzleSolver.hasASolution(rootNode)) << "There should be at least one solution for this puzzle";
}

TEST(PuzzleSolver, isSolvedIn2Moves) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", " ", "┫", " ",
        " ", " ", " ", " ",
        " ", "-", " ", " ",
        " ", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    puzzleSolver.addPossibleMoves(rootNode, 3);
    ASSERT_TRUE(puzzleSolver.hasASolution(rootNode)) << "There should be at least one solution for this puzzle";
}

TEST(PuzzleSolver, noSolution) {
    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", " ", "┫", " ",
        " ", "|", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    puzzleSolver.addPossibleMoves(rootNode, 3);
    ASSERT_FALSE(puzzleSolver.hasASolution(rootNode)) << "There should be at no solution for this puzzle";
}
