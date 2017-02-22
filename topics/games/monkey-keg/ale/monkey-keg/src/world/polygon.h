#ifndef MONKEYKEG_WORLD_POLYGON_H
#define MONKEYKEG_WORLD_POLYGON_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "world/worlditem.h"

namespace MonkeyKeg {
    /**
     * @brief Polygon as a static body filled with a solid color
     */
    class Polygon : WorldItem
    {
        public:
            Polygon(b2World* world, int x, int y);
;
            void update(const float dt) {}
            void render(sf::RenderWindow* window, b2Body* body);
    };
}

#endif
