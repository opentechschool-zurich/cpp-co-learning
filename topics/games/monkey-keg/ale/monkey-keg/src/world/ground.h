#ifndef MONKEYKEG_WORLD_GROUND_H
#define MONKEYKEG_WORLD_GROUND_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "world/worlditem.h"

namespace MonkeyKeg {
    /**
     * @brief Ground rectangle as a static body filled with a solid color
     */
    class Ground : WorldItem
    {
        public:
            Ground(b2World* world, int x, int y);
;
            void update(const float dt) {}
            void render(sf::RenderWindow* window, b2Body* body);
        private:
            const int width = 600;
            const int height = 16;
    };
}

#endif
