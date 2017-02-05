#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <Box2D/Box2D.h>

#include "game.h"

#include "SFMLDebugDraw.h"

#include "world/ground.h"
#include "world/polygon.h"
#include "world/barrel.h"
#include "world/worldcontactlistener.h"

namespace Box2DRolling {

    Game::Game():
        window(sf::VideoMode(800, 600, 32), "Box2D Collision"),
        gravity(0.f, 9.8f),
        world(gravity),
        debugDraw(window),
        barrel(&world, 200, 100)
    {
    }

    void Game::init()
    {
        window.setFramerateLimit(60);

        world.SetDebugDraw(&debugDraw);
        debugDraw.SetFlags(b2Draw::e_shapeBit); //Only draw shapes

        world.SetContactListener(&worldContactListener);
        Ground* ground = new Ground(&world, 400.f, 500.f);
        Polygon* polygon = new Polygon(&world, 200.f, 500.f);
    }

    void Game::update(const float dt)
    {
        for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
            WorldItem* item = static_cast<WorldItem*>(BodyIterator->GetUserData());
            if (item)
            {
                item->update(dt);
            }
        }
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

        world.DrawDebugData();

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
                else if (event.type == sf::Event::MouseButtonPressed)
                {
                }
                else if (event.type == sf::Event::MouseButtonReleased)
                {
                    mouseReleased(event);
                }
                else if (event.type == sf::Event::KeyPressed)
                {
                    keyboardPressed(event);
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
        if (event.key.code == sf::Keyboard::Space) {
        }
    }

    void Game::keyboardReleased(sf::Event event)
    {
        if (event.key.code == sf::Keyboard::Space) {
            // barrel.start();
        }
        else if (event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }
        else if ((event.key.code == sf::Keyboard::Q) && (event.key.control))  {
            window.close();
        }
        else if(event.key.code == sf::Keyboard::F1)
        {
            std::cout << "F1" << std::endl;
            if(debugDraw.GetFlags() & b2Draw::e_shapeBit)
                debugDraw.ClearFlags(b2Draw::e_shapeBit);
            else
                debugDraw.AppendFlags(b2Draw::e_shapeBit);
        }
    }

    void Game::mouseReleased(sf::Event event)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
        }
        else if (event.mouseButton.button == sf::Mouse::Right)
        {
        }
    }

}
