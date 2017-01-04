#ifndef MONKEYKEG_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <Box2D/Box2D.h>

namespace Box2DBodies {
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
        static constexpr float degtorad = 0.0174532925199432957f;
        static constexpr float radtodeg = 57.295779513082320876f;

        b2Vec2 gravity;
        b2World world;

        sf::Texture groundTexture;
        sf::Texture boxTexture;

        void transformBoxes(int x, int y);
        void createBox(int x, int y);
        void createGround(float X, float Y);
    };
}

#endif
