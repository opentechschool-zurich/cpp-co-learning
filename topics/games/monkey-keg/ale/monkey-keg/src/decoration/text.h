#ifndef MONKEYKEG_WORLD_TEXT_H
#define MONKEYKEG_WORLD_TEXT_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <string>

#include "decoration/decoration.h"

namespace MonkeyKeg {
    class Text : public Decoration
    {
        public:
            Text(b2Vec2 pos, std::string content);
;
            void update(const int dt) {}
            void render(sf::RenderWindow* window);
        private:
            sf::Font font;
            sf::Text text;
    };
}

#endif

