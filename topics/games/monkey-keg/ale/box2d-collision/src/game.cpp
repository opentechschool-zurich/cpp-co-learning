#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <Box2D/Box2D.h>

#include "game.h"

#include "world/ground.h"
#include "world/box.h"
#include "world/worldcontactlistener.h"

namespace Box2DCollisions {

    Game::Game():
        window(sf::VideoMode(800, 600, 32), "Box2D Collision"),
        gravity(0.f, 9.8f),
        world(gravity)
    {
    }

    void Game::init()
    {
        window.setFramerateLimit(60);
        world.SetContactListener(&worldContactListener);
        Ground* ground = new Ground(&world, 400.f, 500.f);
    }

    void Game::update(const float dt)
    {
    }

    void Game::render()
    {
        window.clear(sf::Color::White);
        // window.draw(shape);

        for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
            WorldItem* item = static_cast<WorldItem*>(BodyIterator->GetUserData());
            if (item)
            {
                item->render(&window, BodyIterator);
            }
        }

        window.display();
    }

    void Game::run()
    {
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                    }
                    else
                    {
                        Box* box = new Box(&world, event.mouseButton.x, event.mouseButton.y);
                    }
                }
            }

            // TODO: should this go to update()? and should it relate to dt? (ale)
            world.Step(1/60.f, 8, 3);
            sf::Time dt = deltaClock.restart();
            update(dt.asSeconds());
            render();
        }
    }

}
