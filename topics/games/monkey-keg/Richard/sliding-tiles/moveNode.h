#pragma once

#include "direction.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include "move.h"
#include <iostream>

namespace SlidingTiles {

    /**
     * @brief A Move with starting state, ending state and child MoveNodes
     */
    class MoveNode : public Move {
    public:

        /**
         * @brief A single step move for a tile at the supplied position in the
         * supplied direction
         * @param startPosition the game board coordinates of the moving tile
         * @param direction the direction to move in
         * @param startingBoard the starting board (serialised)
         */
        MoveNode(sf::Vector2i startPosition, SlidingTiles::Direction direction, std::vector<std::string> startingBoard)
        : Move(startPosition, direction), startingBoard(startingBoard) {
            id = count;
            ++count;
            //std::cout << "MoveNode constructor being called: #" << id << "\n";
        };

        /**
         * @brief starting board (serialised)
         */
        std::vector <std::string> startingBoard{};

        /**
         * @brief ending board (serialised)
         */
        std::vector <std::string> endingBoard{};

        /**
        * @brief sets the ending board state
        */
        void setEndingBoard(const std::vector <std::string> & serialisedGame) {
            endingBoard = serialisedGame;
        }

        /**
         * @brief next moves
         */
        std::vector <SlidingTiles::MoveNode> possibleMoves{};

        /**
         * @brief explains the move
         */
        std::string toString(const int & indent) {
            std::stringstream ss;
            ss << std::string(indent, ' ') << "Move #" << id << " startPosition: [" << startPosition.x
                    << "][" << startPosition.y << "]"
                    << " direction: " << directionToString(direction) << " possibleMoves: " << possibleMoves.size() << "\n";
            for (int i = 0; i < possibleMoves.size(); ++i) {
                ss << std::string(indent, ' ') << "possibleMove[" << i << "] -->\n";
                ss << possibleMoves[i].toString(indent + 2);
            }
            return ss.str();
        }

        /**
         * @brief explains the move
         */
        virtual std::string toString() {
            return toString(0);
        }

        /**
         * @brief counter
         */
        static int count;

        /**
         * @brief My id
         */
        int id;

    };

} // namespace SlidingTiles
