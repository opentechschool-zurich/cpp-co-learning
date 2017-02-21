#ifndef MONKEYKEG_WORLD_WORLDITEM_H
#define MONKEYKEG_WORLD_WORLDITEM_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace Box2DRolling {

    class WorldItem
    {
        public:
            virtual void update(const float dt) = 0;
            virtual void render(sf::RenderWindow* window, b2Body* body) = 0;
            void startContact() {contact++;}
            void endContact() {contact--;}
        protected:
            int contact{0};
            static constexpr float scale = 30.f;
            // static constexpr float scale = 1.f;
            static constexpr float degtorad = 0.0174532925199432957f;
            static constexpr float radtodeg = 57.295779513082320876f;
    };

}
#endif
