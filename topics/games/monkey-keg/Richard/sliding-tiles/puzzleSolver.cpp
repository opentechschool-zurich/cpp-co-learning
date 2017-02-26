#include "puzzleSolver.h"
#include <queue>

using namespace SlidingTiles;


//std::vector<SlidingTiles::MoveNode> PuzzleSolver::possibleMoves(const std::vector<std::string> & gameState) {

std::vector<SlidingTiles::MoveNode> PuzzleSolver::possibleMoves(const MoveNode & parentNode) {
    MoveNode moveNode{sf::Vector2i{-1, -1}, Direction::Unknown, parentNode.endingBoard};
    moveNode.endingBoard = parentNode.endingBoard;
    gameBoard.loadGame(parentNode.endingBoard);
    //std::cout << moveNode.toString();
    for (int x = 0; x < GameBoard::boardSize; ++x)
        for (int y = 0; y < GameBoard::boardSize; ++y) {
            sf::Vector2i position{x, y};
            if (gameBoard.tiles[x][y].isMoveable) {
                if (parentNode.direction != Direction::GoDown && gameBoard.canSlideTile(Move{position, Direction::GoUp})) {
                    MoveNode childNode{position, Direction::GoUp, moveNode.startingBoard};
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
                if (parentNode.direction != Direction::GoUp && gameBoard.canSlideTile(Move{position, Direction::GoDown})) {
                    MoveNode childNode{position, Direction::GoDown, moveNode.startingBoard};
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
                if (parentNode.direction != Direction::GoRight && gameBoard.canSlideTile(Move{position, Direction::GoLeft})) {
                    MoveNode childNode{position, Direction::GoLeft, moveNode.startingBoard};
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
                if (parentNode.direction != Direction::GoLeft && gameBoard.canSlideTile(Move{position, Direction::GoRight})) {
                    MoveNode childNode{position, Direction::GoRight, moveNode.startingBoard};
                    gameBoard.slideTile(childNode);
                    childNode.setEndingBoard(gameBoard.serialiseGame());
                    moveNode.possibleMoves.push_back(childNode);
                    gameBoard.loadGame(parentNode.endingBoard); // restore
                }
            }
        }
    //std::cout << "Explaining: " << moveNode.toString();
    return moveNode.possibleMoves;
}

void PuzzleSolver::addPossibleMoves(MoveNode &parentNode, const int & levels) {
    //std::cout << "\n\naddPossibleMoves levels: " << levels << " " << parentNode.toString();

    //std::vector<MoveNode> possMoves = possibleMoves(parentNode.endingBoard);
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

/*std::vector<Solution> PuzzleSolver::solutions(const std::vector<std::string> & gameState, const std::vector<MoveNode> & possibleMoves) {
    std::vector<Solution> solutions{};
    for (MoveNode moveNode : possibleMoves) {
        //gameBoard.loadGame(gameState);
        
        Solution currentSolution{};
        //std::cout << "Testing: " << moveNode.toString();
        currentSolution.moves.push_back(moveNode);
        gameBoard.slideTile(moveNode);
        std::vector<sf::Vector2i> solutionPath = gameBoard.isSolved();
        if (solutionPath.size() > 0) {
            solutions.push_back(currentSolution);
            //std::cout << moveNode.toString() << "winner!\n";
        }
    }
    return solutions;
}*/

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
