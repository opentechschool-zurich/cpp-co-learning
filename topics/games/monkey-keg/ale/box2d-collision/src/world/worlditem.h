#ifndef MONKEYKEG_WORLD_WORLDITEM_H
#define MONKEYKEG_WORLD_WORLDITEM_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace Box2DCollisions {

    class WorldItem
    {
        public:
            virtual void render(sf::RenderWindow* window, b2Body* body) = 0;
            void startContact() {contact++;}
            void endContact() {contact--;}
        protected:
            int contact{0};
            static constexpr float scale = 30.f;
    };

}
#endif
