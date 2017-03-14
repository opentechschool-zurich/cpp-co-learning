#ifndef MONKEYKEG_WORLD_BARREL_H
#define MONKEYKEG_WORLD_BARREL_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "world/worlditem.h"

namespace MonkeyKeg {
    /**
     * @brief Barrel rectangle as a dynamic body filled with a texture loaded from a file
     */
    class Barrel : WorldItem
    {
        public:
            Barrel(b2World* world, int x, int y);

            void update(const int dt);
            void render(sf::RenderWindow* window, b2Body* body);

        private:
            sf::Texture boxTexture;
            sf::Texture barrelRedTexture;

            enum Direction{Stopped, Left, Right, Up, Down};
            Direction direction{Stopped};

            int jumpStepsLeft{0};

            b2Body* Body;
    };
}

#endif

