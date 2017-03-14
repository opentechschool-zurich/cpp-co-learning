#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <Box2D/Box2D.h>

#include "game.h"

#include "SFMLDebugDraw.h"

#include <algorithm>  // for_each
#include <functional> // bind

#include "world/ground.h"
#include "world/polygon.h"
#include "world/barrel.h"
#include "world/worlditem.h"
#include "world/worldcontactlistener.h"
#include "decoration/text.h"

namespace MonkeyKeg {

    Game::Game():
        window(sf::VideoMode(800, 600, 32), "Box2D Collision"),
        world(b2Vec2(0.f, 9.8f)), // world(gravity)
        hero(&world, 200, 100),
        debugDraw(window)
    {
        window.setFramerateLimit(60);

        world.SetDebugDraw(&debugDraw);
        debugDraw.SetFlags(b2Draw::e_shapeBit); //Only draw shapes

        world.SetContactListener(&worldContactListener);
        // Text* text = new Text(&world, b2Vec2(200, 200), "100,100");
        // TODO: try to make decoration a vector of Decoration
        decoration.push_back(std::make_unique<Text>(b2Vec2(100, 100), "100,100"));
        Ground* wallLeft = new Ground(&world, b2Vec2(100, 100), b2Vec2(100, 450));
        Ground* wallRight = new Ground(&world, b2Vec2(700, 100), b2Vec2(700, 500));
        Ground* ground = new Ground(&world, b2Vec2(100, 500), b2Vec2(700, 450));
        Ground* level1 = new Ground(&world, b2Vec2(100, 150), b2Vec2(650, 200));
        Ground* level2 = new Ground(&world, b2Vec2(150, 300), b2Vec2(700, 250));
        Ground* level3 = new Ground(&world, b2Vec2(100, 350), b2Vec2(650, 400));

        Barrel* barrel = new Barrel(&world, 200, 100);
    }

    /**
     * @param dt delta time in milliseconds
     */
    void Game::update(const int dt)
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

        for(const auto& item : decoration)
        {
                item->render(&window);
        }

        // std::for_each(decoration.begin(), decoration.end(), 
            // std::bind(&Decoration::render, std::placeholders::_1, &window));
        // std::for_each(decoration.begin(), decoration.end(), 
            // [window](Text& item) {item->render(&window);});

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
            update(dt.asMilliseconds());
            render();
        }
    }

    void Game::keyboardPressed(sf::Event event)
    {
        if (event.key.code == sf::Keyboard::L) {
            hero.startMoveRight();
        }
        else if (event.key.code == sf::Keyboard::J) {
            hero.startMoveLeft();
        }
        else if (event.key.code == sf::Keyboard::I) {
            hero.startMoveUp();
        }
        else if (event.key.code == sf::Keyboard::K) {
            hero.startMoveDown();
        }
    }

    void Game::keyboardReleased(sf::Event event)
    {
        if (event.key.code == sf::Keyboard::Space) {
            hero.startJump();
        }
        else if (event.key.code == sf::Keyboard::L) {
            hero.stopMove();
        }
        else if (event.key.code == sf::Keyboard::J) {
            hero.stopMove();
        }
        else if (event.key.code == sf::Keyboard::I) {
            hero.stopMove();
        }
        else if (event.key.code == sf::Keyboard::K) {
            hero.stopMove();
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
