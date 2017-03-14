#ifndef MONKEYKEG_WORLD_HERO_H
#define MONKEYKEG_WORLD_HERO_H

#include <vector>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "world/worlditem.h"

namespace MonkeyKeg {
    /**
     * @brief Box rectangle as a dynamic body filled with a texture loaded from a file
     */
    class Hero : WorldItem
    {
        public:
            Hero(b2World* world, int x, int y);

            void update(const int dt);
            void render(sf::RenderWindow* window, b2Body* body);

            void startMoveLeft();
            void startMoveRight();
            void startMoveUp();
            void startMoveDown();
            void stopMove();
            void startJump();
            void move();
            void jump();
        private:
            std::vector<sf::Texture> heroWalkingTexture;
            sf::Texture boxRedTexture;

            enum Direction{Stopped, Left, Right, Up, Down};
            Direction direction{Stopped};

            int costumeFrequency{250}; // change every half a second
            int costumeTTL{costumeFrequency}; // time to live
            int costumeIndex{0}; // the current costume

            int jumpStepsLeft{0};

            b2Body* Body;
    };
}

#endif


