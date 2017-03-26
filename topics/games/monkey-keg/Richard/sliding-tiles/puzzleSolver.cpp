#include "puzzleSolver.h"
#include <queue>
#include <assert.h> // assert

using namespace SlidingTiles;

const int PuzzleSolver::DEFAULT_DEPTH;

std::vector<MoveNode> PuzzleSolver::possibleMoves(const MoveNode & parentNode) {
    assert(parentNode.startPosition.x >= -1 && parentNode.startPosition.x <= GameBoard::boardSize);
    assert(parentNode.startPosition.y >= -1 && parentNode.startPosition.y <= GameBoard::boardSize);

    MoveNode moveNode{sf::Vector2i{-1, -1}, Direction::Unknown};
    moveNode.endingBoard = parentNode.endingBoard;
    gameBoard.loadGame(parentNode.endingBoard);
    for (int x = 0; x < GameBoard::boardSize; ++x)
        for (int y = 0; y < GameBoard::boardSize; ++y) {
            sf::Vector2i position{x, y};
            if (gameBoard.tiles[x][y].isMoveable) {
                if (parentNode.direction != Direction::GoDown && gameBoard.canSlideTile(Move{position, Direction::GoUp})) {
                    MoveNode childNode{position, Direction::GoUp};
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
                if (parentNode.direction != Direction::GoUp && gameBoard.canSlideTile(Move{position, Direction::GoDown})) {
                    MoveNode childNode{position, Direction::GoDown};
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
                if (parentNode.direction != Direction::GoRight && gameBoard.canSlideTile(Move{position, Direction::GoLeft})) {
                    MoveNode childNode{position, Direction::GoLeft};
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
                if (parentNode.direction != Direction::GoLeft && gameBoard.canSlideTile(Move{position, Direction::GoRight})) {
                    MoveNode childNode{position, Direction::GoRight};
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
            }
        }
    return moveNode.possibleMoves;
}

void PuzzleSolver::addPossibleMoves(MoveNode &parentNode, const int levels) {
    assert(parentNode.startPosition.x >= -1 && parentNode.startPosition.x <= GameBoard::boardSize);
    assert(parentNode.startPosition.y >= -1 && parentNode.startPosition.y <= GameBoard::boardSize);
    //std::cout << "\n\naddPossibleMoves levels: " << levels << " " << parentNode.toString();

    std::vector<MoveNode> possMoves = possibleMoves(parentNode);
    //std::cout << "Entering if with levels: " << levels << "\n";
    for (MoveNode & mn : possMoves) {
        // note the & above to ensure we work with the members and not a copy
        mn.depth = parentNode.depth + 1;
        if (levels > 0) {
            addPossibleMoves(mn, levels - 1);
        }
    }
    // note do the insert after the recursive call above because insert copies the object and it might copy without the content in the vector!
    parentNode.possibleMoves.insert(std::end(parentNode.possibleMoves), std::begin(possMoves), std::end(possMoves));
}

MoveNode PuzzleSolver::getTree(const std::vector<std::string> & game, int depth) {
    MoveNode rootNode{};
    rootNode.endingBoard = game;
    addPossibleMoves(rootNode, depth);
    return rootNode;
}

MoveNode PuzzleSolver::getTree(const std::wstring & game, int depth) {
    GameBoard gameBoard{};
    gameBoard.loadGame(game);
    return getTree(gameBoard.serialiseGame(), depth);
}

int PuzzleSolver::hasASolution(const MoveNode & node) {
    assert(node.startPosition.x >= -1 && node.startPosition.x <= GameBoard::boardSize);
    assert(node.startPosition.y >= -1 && node.startPosition.y <= GameBoard::boardSize);
    // inspired by https://gist.github.com/douglas-vaz/5072998
    std::queue<MoveNode> Q;
    Q.push(node);
    while (!Q.empty()) {
        MoveNode t = Q.front();
        Q.pop();
        gameBoard.loadGame(t.endingBoard);
        if (gameBoard.isSolved().size() > 0) {
            return t.depth;
        };
        for (int i = 0; i < t.possibleMoves.size(); ++i) {
            Q.push(t.possibleMoves[i]);
        }
    }
    return -1;
}

void PuzzleSolver::generateGames(int games) {
    GameBoard gameBoard{};
    PuzzleSolver puzzleSolver;
    while (--games >= 0) {
        int emptyTiles = (rand() % 13) + 1;
        int count{0};
        std::cout << "trying a game: " << ++count << " with empty tiles: " << emptyTiles << " max moves: 4";
        do {
            gameBoard.randomGame(emptyTiles);
            MoveNode rootNode = puzzleSolver.getTree(gameBoard.serialiseGame(), 4);
            std::cout << ".";
            
            int solutionDepth = puzzleSolver.hasASolution(rootNode);
            if (solutionDepth > -1) {
                std::cout << "\nEmpty Tiles: " << emptyTiles << " Solution Depth: " << solutionDepth << " Game Board: " << gameBoard.serialiseGameToString() << "\n";
                count = -1;
            }
        } while (count > -1);
    }
}