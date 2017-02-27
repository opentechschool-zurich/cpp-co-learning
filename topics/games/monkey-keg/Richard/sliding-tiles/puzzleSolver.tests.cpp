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

TEST(PuzzleSolver, addPossibleMoves) {
    // builds on possibleMovesOne
    std::wstring game {L"├-┫             "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    puzzleSolver.addPossibleMoves(rootNode, 1);
    ASSERT_THAT(rootNode.possibleMoves.size(), 1);

    MoveNode onlyChild = rootNode.possibleMoves[0];
    ASSERT_THAT(onlyChild.possibleMoves.size(), 3);
    int up{0};
    int down{0};
    int left{0};
    int right{0};
    for (auto node : onlyChild.possibleMoves) {
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
    ASSERT_EQ(right, 1);
}

TEST(PuzzleSolver, addPossibleMoves3Deep) {
    // builds on addPossibleMoves which builds on possibleMovesOne
    std::wstring game {L"├-┫             "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    puzzleSolver.addPossibleMoves(rootNode, 3);
    ASSERT_THAT(rootNode.possibleMoves.size(), 1);

    MoveNode onlyChild = rootNode.possibleMoves[0];
    ASSERT_THAT(onlyChild.possibleMoves.size(), 3);
    int up{0};
    int down{0};
    MoveNode downNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    int left{0};
    MoveNode leftNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    int right{0};
    MoveNode rightNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    for (auto node : onlyChild.possibleMoves) {
        if (node.direction == Direction::GoDown) {
            ++down;
            ASSERT_EQ(node.possibleMoves.size(), 3);
            downNode = node;
        } else if (node.direction == Direction::GoUp) {
            ++up;
        } else if (node.direction == Direction::GoLeft) {
            ++left;
            ASSERT_EQ(node.possibleMoves.size(), 1);
            leftNode = node;
        } else if (node.direction == Direction::GoRight) {
            ++right;
            ASSERT_EQ(node.possibleMoves.size(), 2);
            rightNode = node;
        }
    }
    ASSERT_EQ(up, 0);
    ASSERT_EQ(down, 1);
    ASSERT_EQ(left, 1);
    ASSERT_EQ(right, 1);

    // Second Level:
    int up2{0};
    int down2{0};
    int left2{0};
    int right2{0};
    for (auto node : downNode.possibleMoves) {
        if (node.direction == Direction::GoDown) {
            ++down2;
            ASSERT_EQ(node.possibleMoves.size(), 2);
        } else if (node.direction == Direction::GoUp) {
            ++up2;
        } else if (node.direction == Direction::GoLeft) {
            ++left2;
            ASSERT_EQ(node.possibleMoves.size(), 2);
        } else if (node.direction == Direction::GoRight) {

            ++right2;
            ASSERT_EQ(node.possibleMoves.size(), 3);
        }
    }
    ASSERT_EQ(up2, 0);
    ASSERT_EQ(down2, 1);
    ASSERT_EQ(left2, 1);
    ASSERT_EQ(right2, 1);

}

TEST(PuzzleSolver, isSolvedIn1Move) {

    std::string game [GameBoard::boardSize][GameBoard::boardSize]{"├", " ", "┫", " ",
        " ", "-", " ", " ",
        " ", " ", " ", " ",
        " ", " ", " ", " "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i
        {-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
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
    MoveNode rootNode{sf::Vector2i
        {-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    puzzleSolver.addPossibleMoves(rootNode, 3);
    ASSERT_TRUE(puzzleSolver.hasASolution(rootNode)) << "There should be at least one solution for this puzzle";
}

TEST(PuzzleSolver, noSolution) {
    std::wstring game {L"├ ┫  |          "};
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    MoveNode rootNode{sf::Vector2i
        {-1, -1}, Direction::Unknown, gameBoard.serialiseGame()};
    rootNode.endingBoard = gameBoard.serialiseGame();
    PuzzleSolver puzzleSolver;
    puzzleSolver.addPossibleMoves(rootNode, 3);
    ASSERT_FALSE(puzzleSolver.hasASolution(rootNode)) << "There should be at no solution for this puzzle";
}
