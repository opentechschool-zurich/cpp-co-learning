#pragma once

#include <SFML/Audio.hpp>
#include "json.hpp"

using json = nlohmann::json;

namespace SlidingTiles {

    /**
     * @brief Loads the sounds in the constructor and can then be called repeatedly to play a winner sound bite
     */
    class WinnerSounds {
    public:
        WinnerSounds(const json & winnerSoundBitesArray);
        /**
         * @brief plays a winner soundbite
         */
        void playWinnerSoundBite();
    private:
        /**
         * @brief Winner sounds
         */
        std::vector<sf::SoundBuffer> winnerSoundBites;
    };
}

