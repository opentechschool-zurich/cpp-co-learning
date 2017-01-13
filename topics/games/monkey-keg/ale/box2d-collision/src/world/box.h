#ifndef MONKEYKEG_WORLD_BOX_H
#define MONKEYKEG_WORLD_BOX_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "world/worlditem.h"

namespace Box2DCollisions {
    /**
     * @brief Box rectangle as a dynamic body filled with a texture loaded from a file
     */
    class Box : WorldItem
    {
        public:
            Box(b2World* world, int x, int y);

            void render(sf::RenderWindow* window, b2Body* body);
        private:
            sf::Texture boxTexture;
            sf::Texture boxRedTexture;
    };
}

#endif

