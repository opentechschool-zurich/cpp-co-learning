#include <iostream>
#include "world/barrel.h"

namespace Box2DRolling {
    Barrel::Barrel(b2World* world, int x, int y)
    {
        boxTexture.loadFromFile("assets/box.png");
        barrelRedTexture.loadFromFile("assets/barrel-red.png");

        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x/scale, y/scale);
        // TODO: should the box be a kinematic body?
        BodyDef.type = b2_dynamicBody;
        Body = world->CreateBody(&BodyDef);

        Body->SetUserData(this);

        b2CircleShape Shape;
        // Shape.SetAsBox((32.f/2)/scale, (32.f/2)/scale);
        Shape.m_p.Set((2.f)/scale, (3.f)/scale);
        Shape.m_radius = 0.5f;
        b2FixtureDef FixtureDef;
        FixtureDef.density = 1.f;
        FixtureDef.friction = 0.7f;
        FixtureDef.shape = &Shape;
        Body->CreateFixture(&FixtureDef);
    }

    void Barrel::update(const float dt)
    {
        // jump(); // TODO: move this to update()
        // move();
    }

    void Barrel::render(sf::RenderWindow* window, b2Body* body)
    {
        sf::Sprite Sprite;
        if (contact > 0)
        {
            Sprite.setTexture(barrelRedTexture);
        }
        else
        {
            Sprite.setTexture(boxTexture);
        }
        Sprite.setOrigin(16.f, 16.f);
        Sprite.setPosition(scale * body->GetPosition().x, scale * body->GetPosition().y);
        Sprite.setRotation(body->GetAngle() * 180/b2_pi);
        window->draw(Sprite);
    }
}
