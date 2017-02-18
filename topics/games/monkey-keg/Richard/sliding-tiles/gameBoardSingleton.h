#pragma once
#include "gameBoard.h"


namespace SlidingTiles {

    /**
     * @brief Singleton class that holds the information about the game state
     */
    class GameBoardSingleton : public GameBoard {
    public:
        /**
         * @brief Deleted to enforce singleton pattern
         */
        GameBoardSingleton(GameBoardSingleton const&) = delete;

        /**
         * @brief Deleted to enforce singleton pattern
         */
        void operator=(GameBoardSingleton const&) = delete;

        /**
         * @brief returns the single instance of the GameBoard singleton
         */
        static GameBoardSingleton& getInstance() {
            static GameBoardSingleton instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
            return instance;
        }

    private:
        /**
         * @brief Private constructor for singleton
         */
        GameBoardSingleton();

    };

} // namespace
