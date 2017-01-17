#ifndef MONKEYKEG_WORLD_BOX_H
#define MONKEYKEG_WORLD_BOX_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "world/worlditem.h"

namespace Box2DJump {
    /**
     * @brief Box rectangle as a dynamic body filled with a texture loaded from a file
     */
    class Box : WorldItem
    {
        public:
            Box(b2World* world, int x, int y);

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
            sf::Texture boxTexture;
            sf::Texture boxRedTexture;

            enum Direction{Stopped, Left, Right, Up, Down};
            Direction direction{Stopped};

            int jumpStepsLeft{0};

            b2Body* Body;
    };
}

#endif

