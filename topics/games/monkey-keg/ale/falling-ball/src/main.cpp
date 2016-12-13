#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <Box2D/Box2D.h>

namespace MonkeyKeg {
    class Game
    {
        sf::RenderWindow window;
        sf::CircleShape shape;
        sf::Clock deltaClock;

        b2Vec2 Gravity;
        b2World World;

		sf::Texture GroundTexture;
		sf::Texture BoxTexture;
    public:
        Game():
            window(sf::VideoMode(200, 200), "SFML works!"),
            Gravity(0.f, 9.8f),
            World(Gravity),
            shape(20.f)
        {
        }

        void init()
        {
            window.setFramerateLimit(60),
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(10, 10);

			GroundTexture.loadFromFile("assets/ground.png");
			BoxTexture.loadFromFile("assets/box.png");

        }

        void update(const float dt)
        {
            std::cout << "dt: " << dt << std::endl;
            shape.move(100 * dt, 100 * dt);
        }

        void render()
        {
            window.clear();
            window.draw(shape);
            window.display();
        }

        void run()
        {
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                sf::Time dt = deltaClock.restart();
                update(dt.asSeconds());
                render();
            }
        }

    };
}

int main()
{

    MonkeyKeg::Game game;
    game.init();
    game.run();
    
}
