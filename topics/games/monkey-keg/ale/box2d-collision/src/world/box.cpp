#include "world/box.h"

namespace Box2DCollisions {
    Box::Box(b2World* world, int x, int y)
    {
        boxTexture.loadFromFile("assets/box.png");
        boxRedTexture.loadFromFile("assets/box-red.png");

        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x/scale, y/scale);
        BodyDef.type = b2_dynamicBody;
        b2Body* Body = world->CreateBody(&BodyDef);

        Body->SetUserData(this);

        b2PolygonShape Shape;
        Shape.SetAsBox((32.f/2)/scale, (32.f/2)/scale);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 1.f;
        FixtureDef.friction = 0.7f;
        FixtureDef.shape = &Shape;
        Body->CreateFixture(&FixtureDef);
    }

    void Box::render(sf::RenderWindow* window, b2Body* body)
    {
        sf::Sprite Sprite;
        if (contact > 0)
        {
            Sprite.setTexture(boxRedTexture);
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
