#ifndef MONKEYKEG_GAME_WORLD_WORLDCONTACTLISTENER_H
#define MONKEYKEG_GAME_WORLD_WORLDCONTACTLISTENER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace Box2DJump {
    /**
     * @brief Notify `worlditem`s of contacts
     */
    class WorldContactListener : public b2ContactListener
    {
        public:
            void BeginContact(b2Contact* contact);
            void EndContact(b2Contact* contact);
    };
}

#endif
