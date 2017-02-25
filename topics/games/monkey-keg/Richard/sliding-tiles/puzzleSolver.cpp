#include "puzzleSolver.h"
#include <queue>

using namespace SlidingTiles;


std::vector<SlidingTiles::MoveNode> PuzzleSolver::possibleMoves(const std::vector<std::string> & gameState) {
    //MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, serialiseGame()};
    MoveNode rootNode{sf::Vector2i{-1, -1}, Direction::Unknown, gameState};
    //rootNode.endingBoard = serialiseGame();
    rootNode.endingBoard = gameState;
    for (int x = 0; x < GameBoard::boardSize; ++x)
        for (int y = 0; y < GameBoard::boardSize; ++y) {
            sf::Vector2i position{x, y};
            gameBoard.loadGame(gameState);
            if (gameBoard.tiles[x][y].isMoveable) {
                if (gameBoard.canSlideTile(Move{position, Direction::GoUp})) {
                    SlidingTiles::MoveNode moveNode{position, Direction::GoUp, rootNode.startingBoard};
                    gameBoard.slideTile(moveNode);
                    moveNode.setEndingBoard(gameBoard.serialiseGame());
                    rootNode.possibleMoves.push_back(moveNode);
                    gameBoard.loadGame(rootNode.startingBoard);
                    //std::cout << "Creating a possible move(GoUp): " << moveNode.toString();
                }
                if (gameBoard.canSlideTile(Move{position, Direction::GoDown})) {
                    SlidingTiles::MoveNode moveNode{position, Direction::GoDown, rootNode.startingBoard};
                    gameBoard.slideTile(moveNode);
                    moveNode.setEndingBoard(gameBoard.serialiseGame());
                    rootNode.possibleMoves.push_back(moveNode);
                    gameBoard.loadGame(rootNode.startingBoard);
                    //std::cout << "Creating a possible move(GoDown): " << moveNode.toString();
                }
                if (gameBoard.canSlideTile(Move{position, Direction::GoLeft})) {
                    SlidingTiles::MoveNode moveNode{position, Direction::GoLeft, rootNode.startingBoard};
                    gameBoard.slideTile(moveNode);
                    moveNode.setEndingBoard(gameBoard.serialiseGame());
                    rootNode.possibleMoves.push_back(moveNode);
                    gameBoard.loadGame(rootNode.startingBoard);
                    //std::cout << "Creating a possible move(GoLeft): " << moveNode.toString();
                }
                if (gameBoard.canSlideTile(Move{position, Direction::GoRight})) {
                    SlidingTiles::MoveNode moveNode{position, Direction::GoRight, rootNode.startingBoard};
                    gameBoard.slideTile(moveNode);
                    moveNode.setEndingBoard(gameBoard.serialiseGame());
                    rootNode.possibleMoves.push_back(moveNode);
                    gameBoard.loadGame(rootNode.startingBoard);
                    //std::cout << "Creating a possible move(GoRight): " << moveNode.toString();
                }
            }
        }
    return rootNode.possibleMoves;
}


void PuzzleSolver::addPossibleMoves(MoveNode &parentNode, const int & levels) {
    //std::cout << "\n\naddPossibleMoves levels: " << levels << " " << parentNode.toString();

    //std::vector<std::string> priorGameState = gameBoard.serialiseGame();
    //gameBoard.loadGame(parentNode.endingBoard);
    //PuzzleSolver puzzleSolver;
    //std::vector<MoveNode> possMoves = possibleMoves(priorGameState);
    std::vector<MoveNode> possMoves = possibleMoves(parentNode.endingBoard);
    if (levels > 0) {
        //std::cout << "Entering if with levels: " << levels << "\n";
        for (MoveNode & mn : possMoves) {
            // note the & above to ensure we work with the members and not a copy
            addPossibleMoves(mn, levels - 1);
        }
    }
    // note do the insert after the recursive call above because insert copies the object and it might copy without the content in the vector!
    parentNode.possibleMoves.insert(std::end(parentNode.possibleMoves), std::begin(possMoves), std::end(possMoves));
    //std::cout << "parentNode after insert: " << parentNode.toString();
    //std::cout << "finished addPosibleMoves levels: " << levels << " " << parentNode.toString();
    //gameBoard.loadGame(priorGameState);
}


std::vector<Solution> PuzzleSolver::solutions(const std::vector<std::string> & gameState, const std::vector<MoveNode> & possibleMoves) {
    //std::vector<std::string> priorGameState = gameBoard.serialiseGame();
    std::vector<Solution> solutions{};
    for (MoveNode moveNode : possibleMoves) {
        gameBoard.loadGame(gameState);
        Solution currentSolution{};
        //std::cout << "Testing: " << moveNode.toString();
        currentSolution.moves.push_back(moveNode);
        gameBoard.slideTile(moveNode);
        std::vector<sf::Vector2i> solutionPath = gameBoard.isSolved();
        if (solutionPath.size() > 0) {
            solutions.push_back(currentSolution);
            //std::cout << moveNode.toString() << "winner!\n";
        }
        //gameBoard.loadGame(priorGameState);
    }
    return solutions;
}

bool PuzzleSolver::hasASolution(const MoveNode & node) {
    //std::vector<std::string> priorGameState = gameBoard.serialiseGame();
    // inspired by https://gist.github.com/douglas-vaz/5072998
    std::queue<MoveNode> Q;
    Q.push(node);
    while (!Q.empty()) {
        MoveNode t = Q.front();
        Q.pop();
        gameBoard.loadGame(t.endingBoard);
        if (gameBoard.isSolved().size() > 0) {
            //gameBoard.loadGame(priorGameState);
            return true;
        };
        for (int i = 0; i < t.possibleMoves.size(); ++i) {
            Q.push(t.possibleMoves[i]);
        }
    }
    //gameBoard.loadGame(priorGameState);
    return false;
}
