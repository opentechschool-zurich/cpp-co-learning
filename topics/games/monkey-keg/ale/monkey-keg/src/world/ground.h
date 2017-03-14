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
            Ground(b2World* world, int x, int y, int length, int angle);
            Ground(b2World* world, b2Vec2 start, b2Vec2 end);
;
            void update(const int dt) {}
            void render(sf::RenderWindow* window, b2Body* body);
        private:
            int length = 600;
            const int height = 16;
    };
}

#endif
