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

        const int groundWidth = 600;
        const int groundHeight = 16;


    private:
        sf::RenderWindow window;
        // sf::CircleShape shape;
        sf::Clock deltaClock;

        /** for converting between pixel and real-world coordinates*/
        static constexpr float scale = 30.f;
        static constexpr float degtorad = 0.0174532925199432957f;
        static constexpr float radtodeg = 57.295779513082320876f;

        const b2Vec2 GRAVITY { 0.f, 9.81f };
        b2World world;

        sf::Texture groundTexture;
        sf::Texture boxTexture;

        void transformBoxes(int x, int y);
        void createBox(int x, int y);
        void createGround(b2World & world, const float X, const float Y);


    };
}

#endif
