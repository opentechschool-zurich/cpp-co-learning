#ifndef MONKEYKEG_WORLD_DECORATION_H
#define MONKEYKEG_WORLD_DECORATION_H

#include <SFML/Graphics.hpp>

namespace MonkeyKeg {

    class Decoration
    {
        public:
            virtual void update(const float dt) = 0;
            virtual void render(sf::RenderWindow* window) = 0;
            void startContact() {contact++;}
            void endContact() {contact--;}
        protected:
            int contact{0};
            static constexpr float scale = 30.f;
            static constexpr float degtorad = 0.0174532925199432957f;
            static constexpr float radtodeg = 57.295779513082320876f;
    };

}
#endif
