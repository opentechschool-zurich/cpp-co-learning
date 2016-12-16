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

    public:
        Game():
            window(sf::VideoMode(200, 200), "SFML works!"),
            shape(20.f)
        {
        }

        void init()
        {
            window.setFramerateLimit(60),
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(10, 10);
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
