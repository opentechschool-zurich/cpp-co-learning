#ifndef MONKEYKEG_GAME_WORLD_WORLDCONTACTLISTENER_H
#define MONKEYKEG_GAME_WORLD_WORLDCONTACTLISTENER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Audio.hpp>
#include <deque>

namespace Box2DCollisions {
    /**
     * @brief Notify `worlditem`s of contacts
     */
    class WorldContactListener : public b2ContactListener
    {
        public:
            void BeginContact(b2Contact* contact);
            void EndContact(b2Contact* contact);
            WorldContactListener();
        private:
            sf::SoundBuffer boxCrashSoundBuffer;
            std::deque<sf::Sound> playingSounds{};
    };
}

#endif
