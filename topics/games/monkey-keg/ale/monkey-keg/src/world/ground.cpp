#include "world/ground.h"
#include "game.h"

/**
 * TODO:
 * - rename ground as floor
 */

namespace MonkeyKeg {
    Ground::Ground(b2World* world, int x, int y, int length, int angle) :
        length(length)
    {
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x/scale, y/scale);
        BodyDef.type = b2_staticBody;
        b2Body* Body = world->CreateBody(&BodyDef);

        Body->SetUserData(this);

        b2PolygonShape Shape;
        Body->SetTransform(Body->GetWorldCenter(), angle * degtorad);
        Shape.SetAsBox((length/2)/scale, (height/2)/scale);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 0.f;
        FixtureDef.shape = &Shape;
        Body->CreateFixture(&FixtureDef);
    }

    /**
     * TODO: calculate length and angle according to the start and end points
     */
    Ground::Ground(b2World* world, b2Vec2 start, b2Vec2 end)
    {
        /*
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x/scale, y/scale);
        BodyDef.type = b2_staticBody;
        b2Body* Body = world->CreateBody(&BodyDef);

        Body->SetUserData(this);

        b2PolygonShape Shape;
        Body->SetTransform(Body->GetWorldCenter(), angle * degtorad);
        Shape.SetAsBox((length/2)/scale, (height/2)/scale);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 0.f;
        FixtureDef.shape = &Shape;
        Body->CreateFixture(&FixtureDef);
        */
    }

    void Ground::render(sf::RenderWindow* window, b2Body* body)
    {
        sf::RectangleShape rectangle(sf::Vector2f(length, height));
        rectangle.setFillColor(sf::Color(50,50,250));

        rectangle.setOrigin(length/2, height/2);
        rectangle.setPosition(scale * body->GetPosition().x, scale * body->GetPosition().y);
        rectangle.setRotation(body->GetAngle() * radtodeg);

        window->draw(rectangle);
    }
}