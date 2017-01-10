#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <Box2D/Box2D.h>

#include "game.h"

namespace Box2DBodies {
    Game::Game():
        window(sf::VideoMode(800, 600, 32), "Box2D Bodies"),
        world(GRAVITY)
    {
    }

    sf::Font font;
    void Game::init()
    {
        window.setFramerateLimit(60),
        boxTexture.loadFromFile("assets/box.png");
        createGround(world, 400.f, 500.f);


        if (!font.loadFromFile("assets/ChangaOne-Regular.ttf"))
            std::cout << "Can't load font ./assets/ChangaOne-Regular.ttf" << std::endl;

        bannerText.setFont(font);
        bannerText.setCharacterSize(30);
        bannerText.setStyle(sf::Text::Bold);
        bannerText.setColor(sf::Color::Black);
        bannerText.setString("Left-click to drop, right-click to rotate");
        bannerText.setPosition(30, 10);

    }

    void Game::update(const float dt)
    {
        // std::cout << "dt: " << dt << std::endl;
        // shape.move(100 * dt, 100 * dt);
        for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
            b2Vec2 pos = BodyIterator->GetPosition();
            // std::cout << "y: " << pos.y / scale << std::endl;
            if ((pos.y / scale) > 0.8f)
            {
                world.DestroyBody(BodyIterator);
            }
        }
    }

    void Game::render()
    {
        window.clear(sf::Color::White);

        window.draw(bannerText);

        for (b2Body* body = world.GetBodyList(); body != 0; body = body->GetNext())
        // for (auto BodyIterator : world.GetBodyList())
        {
            // TODO: we should probably use BodyDef.UserData to keep them apart (ale)
            if (body->GetType() == b2_dynamicBody)
            {
                sf::Sprite box;
                box.setTexture(boxTexture);
                box.setOrigin(16.f, 16.f);
                box.setPosition(scale * body->GetPosition().x, scale * body->GetPosition().y);
                box.setRotation(body->GetAngle() * 180/b2_pi);
                window.draw(box);
            }
            else
            {
                sf::RectangleShape rectangle(sf::Vector2f(Game::groundWidth, Game::groundHeight));
                rectangle.setFillColor(sf::Color(50,50,250));
                rectangle.setPosition(body->GetPosition().x * scale - Game::groundWidth /2, body->GetPosition().y * scale - Game::groundHeight /2);
                rectangle.setRotation(180/b2_pi * body->GetAngle());
                window.draw(rectangle);
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
                        transformBoxes(event.mouseButton.x, event.mouseButton.y);
                    }
                    else
                        createBox(event.mouseButton.x, event.mouseButton.y);
                }
            }

            // TODO: should this go to update()? and should it relate to dt? (ale)
            world.Step(1/60.f, 8, 3);
            sf::Time dt = deltaClock.restart();
            update(dt.asSeconds());
            render();
        }
    }

    void Game::transformBoxes(int x, int y)
    {
        for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
            if (BodyIterator->GetType() == b2_dynamicBody)
            {
                BodyIterator->SetTransform(BodyIterator->GetPosition(), BodyIterator->GetAngle() + (15 * degtorad));
                // BodyIterator->SetLinearVelocity(b2Vec2( -200 / scale, 200 / scale ) ); //moving up and left 5 units per second
                // BodyIterator->SetAngularVelocity(-90 * degtorad ); //90 degrees per second clockwise

            }
        }
    }

    void Game::createBox(const int x, const int y)
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = b2Vec2(x/scale, y/scale);
        bodyDef.angle = 0;

        b2Body* Body = world.CreateBody(&bodyDef);

        b2PolygonShape Shape;
        Shape.SetAsBox((32.f/2)/scale, (32.f/2)/scale);

        b2FixtureDef FixtureDef;
        FixtureDef.shape = &Shape;
        FixtureDef.density = 0.f;

        Body->CreateFixture(&FixtureDef);
    }

    void Game::createGround(b2World & world, const float x, const float y)
    {
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x/scale, y/scale);
        BodyDef.type = b2_staticBody;
        b2Body* Body = world.CreateBody(&BodyDef);

        b2PolygonShape Shape;
        Shape.SetAsBox((Game::groundWidth/2)/scale, (Game::groundHeight/2)/scale);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 0.f;
        FixtureDef.shape = &Shape;
        Body->CreateFixture(&FixtureDef);
    }
}
