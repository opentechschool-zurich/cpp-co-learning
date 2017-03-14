#ifndef MONKEYKEG_GAME_H
#define MONKEYKEG_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <Box2D/Box2D.h>

#include <vector>
#include "decoration/text.h"

#include "SFMLDebugDraw.h"

#include "world/barrel.h"
#include "world/hero.h"
#include "world/worldcontactlistener.h"

namespace MonkeyKeg {

    class Game
    {
    public:
        Game();

        void update(const int dt);
        void render();
        void run();

    private:
        sf::RenderWindow window;
        // sf::CircleShape shape;
        sf::Clock deltaClock;

        b2World world;
        // std::vector<WorldItem *> decoration;
        std::vector< std::unique_ptr<Decoration> > decoration;

        Hero hero;

        /*
        template<typename D>
        void addDecoration(const D& thing) {
            decoration.push_back(make_unique<D>(thing));
        }
        */

        SFMLDebugDraw debugDraw;

        WorldContactListener worldContactListener;

        /**
         * @brief Actions to be triggered while keys are pressed
         */
        void keyboardPressed(sf::Event event);

        /**
         * @brief Actions to be triggered when keys are released
         */
        void keyboardReleased(sf::Event event);

        /**
         * @brief Actions to be triggered when the mouse button is released
         */
        void mouseReleased(sf::Event event);
    };
}
#endif
