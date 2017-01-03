#ifndef MONKEYKEG_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <Box2D/Box2D.h>

namespace MonkeyKeg {
    class Game
    {
    public:
        Game();

        void init();
        void update(const float dt);
        void render();
        void run();

    private:
        sf::RenderWindow window;
        // sf::CircleShape shape;
        sf::Clock deltaClock;

        /** for converting between pixel and real-world coordinates*/
        static constexpr float scale = 30.f;

        b2Vec2 gravity;
        b2World world;

        sf::Texture groundTexture;
        sf::Texture boxTexture;

        void createBox(int x, int y);
        void createGround(float X, float Y);
    };
}

#endif
