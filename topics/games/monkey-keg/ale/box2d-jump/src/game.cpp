#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <Box2D/Box2D.h>

#include "game.h"

#include "world/ground.h"
#include "world/box.h"
#include "world/worldcontactlistener.h"

namespace Box2DJump {

    Game::Game():
        window(sf::VideoMode(800, 600, 32), "Box2D Collision"),
        gravity(0.f, 9.8f),
        world(gravity),
        box(&world, 200, 100)
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
            /* Events can be individually polled from sf::Keyboard or by checking the polled events.
             * The first way is better suited for high performance / continues polling (keeping down the key)
             * In this case, the second approach probably fits better
             * http://www.sfml-dev.org/tutorials/2.4/window-inputs.php
             */
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonReleased)
                {
                    mouse(event);
                }
                else if (event.type == sf::Event::KeyPressed)
                {
                }
                else if (event.type == sf::Event::KeyReleased)
                {
                    keyboardReleased(event);
                }
            }

            // TODO: should this go to update()? and should it relate to dt? (ale)
            world.Step(1/60.f, 8, 3);
            sf::Time dt = deltaClock.restart();
            update(dt.asSeconds());
            render();
        }
    }

    void Game::keyboardPressed(sf::Event event)
    {
    }

    void Game::keyboardReleased(sf::Event event)
    {
        if (event.key.code == sf::Keyboard::L) {
            // TODO: right
            box.moveRight();
        }
        else if (event.key.code == sf::Keyboard::H) {
            // TODO: jump
            box.moveLeft();
        }
        else if (event.key.code == sf::Keyboard::Space) {
        }
        else if (event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }
        else if ((event.key.code == sf::Keyboard::Q) && (event.key.control))  {
            window.close();
        }
   
    }

    void Game::mouse(sf::Event event)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
        }
        else if (event.mouseButton.button == sf::Mouse::Right)
        {
        }
    }

}
