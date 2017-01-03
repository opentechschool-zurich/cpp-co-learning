#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <Box2D/Box2D.h>

#include "game.h"

namespace MonkeyKeg {
    Game::Game():
        window(sf::VideoMode(800, 600, 32), "Test"),
        gravity(0.f, 9.8f),
        world(gravity)
        // shape(20.f)
    {
    }

    void Game::init()
    {
        window.setFramerateLimit(60),

        createGround(400.f, 500.f);
        groundTexture.loadFromFile("assets/ground.png");

        boxTexture.loadFromFile("assets/box.png");

    }

    void Game::update(const float dt)
    {
        // std::cout << "dt: " << dt << std::endl;
        // shape.move(100 * dt, 100 * dt);
    }

    void Game::render()
    {
        window.clear(sf::Color::White);
        // window.draw(shape);

        for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        // for (auto BodyIterator : world.GetBodyList())
        {
            // TODO: we should probably use BodyDef.UserData to keep them apart (ale)
            if (BodyIterator->GetType() == b2_dynamicBody)
            {
                sf::Sprite Sprite;
                Sprite.setTexture(boxTexture);
                Sprite.setOrigin(16.f, 16.f);
                Sprite.setPosition(scale * BodyIterator->GetPosition().x, scale * BodyIterator->GetPosition().y);
                Sprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
                window.draw(Sprite);
            }
            else
            {
                sf::Sprite GroundSprite;
                GroundSprite.setTexture(groundTexture);
                GroundSprite.setOrigin(400.f, 8.f);
                GroundSprite.setPosition(BodyIterator->GetPosition().x * scale, BodyIterator->GetPosition().y * scale);
                GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
                window.draw(GroundSprite);
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
                    createBox(event.mouseButton.x, event.mouseButton.y);
            }

            // TODO: should this go to update()? and should it relate to dt? (ale)
            world.Step(1/60.f, 8, 3);
            sf::Time dt = deltaClock.restart();
            update(dt.asSeconds());
            render();
        }
    }

    void Game::createBox(int x, int y)
    {
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x/scale, y/scale);
        BodyDef.type = b2_dynamicBody;
        b2Body* Body = world.CreateBody(&BodyDef);

        b2PolygonShape Shape;
        Shape.SetAsBox((32.f/2)/scale, (32.f/2)/scale);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 1.f;
        FixtureDef.friction = 0.7f;
        FixtureDef.shape = &Shape;
        Body->CreateFixture(&FixtureDef);
    }

    void Game::createGround(float x, float y)
    {
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x/scale, y/scale);
        BodyDef.type = b2_staticBody;
        b2Body* Body = world.CreateBody(&BodyDef);

        b2PolygonShape Shape;
        Shape.SetAsBox((800.f/2)/scale, (16.f/2)/scale);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 0.f;
        FixtureDef.shape = &Shape;
        Body->CreateFixture(&FixtureDef);
    }
}
