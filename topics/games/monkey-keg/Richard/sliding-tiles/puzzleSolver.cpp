#include "puzzleSolver.h"
#include <queue>
#include <assert.h> // assert

using namespace SlidingTiles;

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

void PuzzleSolver::addPossibleMoves(MoveNode &parentNode, const int & levels) {
    assert(parentNode.startPosition.x >= -1 && parentNode.startPosition.x <= GameBoard::boardSize);
    assert(parentNode.startPosition.y >= -1 && parentNode.startPosition.y <= GameBoard::boardSize);
    //std::cout << "\n\naddPossibleMoves levels: " << levels << " " << parentNode.toString();

    std::vector<MoveNode> possMoves = possibleMoves(parentNode);
    if (levels > 0) {
        //std::cout << "Entering if with levels: " << levels << "\n";
        for (MoveNode & mn : possMoves) {
            // note the & above to ensure we work with the members and not a copy
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


bool PuzzleSolver::hasASolution(const MoveNode & node) {
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
            return true;
        };
        for (int i = 0; i < t.possibleMoves.size(); ++i) {
            Q.push(t.possibleMoves[i]);
        }
    }
    return false;
}
