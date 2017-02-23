#ifndef MONKEYKEG_WORLD_TEXT_H
#define MONKEYKEG_WORLD_TEXT_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <string>

#include "decoration/decoration.h"

namespace MonkeyKeg {
    class Text : Decoration
    {
        public:
            Text(b2Vec2 pos, std::string content);
;
            void update(const float dt) {}
            void render(sf::RenderWindow* window);
        private:
            sf::Font font;
            sf::Text text;
    };
}

#endif

