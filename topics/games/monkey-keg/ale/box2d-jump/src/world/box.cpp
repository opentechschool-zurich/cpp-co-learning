#include <iostream>
#include "world/box.h"

namespace Box2DJump {
    Box::Box(b2World* world, int x, int y)
    {
        boxTexture.loadFromFile("assets/box.png");
        boxRedTexture.loadFromFile("assets/box-red.png");

        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x/scale, y/scale);
        // TODO: should the box be a kinematic body?
        BodyDef.type = b2_dynamicBody;
        Body = world->CreateBody(&BodyDef);

        Body->SetUserData(this);

        b2PolygonShape Shape;
        Shape.SetAsBox((32.f/2)/scale, (32.f/2)/scale);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 1.f;
        FixtureDef.friction = 0.7f;
        FixtureDef.shape = &Shape;
        Body->CreateFixture(&FixtureDef);
    }

    void Box::update(const float dt)
    {
        jump(); // TODO: move this to update()
        move();
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

    void Box::startMoveLeft()
    {
        std::cout << "start left" << std::endl;
        if (contact > 0) {
            direction = Direction::Left;
        }
        // Body->SetLinearVelocity(b2Vec2(-5, 0));
    }
    void Box::startMoveRight()
    {
        std::cout << "start right" << std::endl;
        if (contact > 0) {
            direction = Direction::Right;
        }
        // Body->SetLinearVelocity(b2Vec2(5, 0));
    }

    void Box::startMoveUp()
    {
        std::cout << "start up" << std::endl;
        // TODO: disable gravity?
        if (contact > 0) {
            direction = Direction::Up;
        }
        // Body->SetLinearVelocity(b2Vec2(0, 5));
    }

    void Box::startMoveDown()
    {
        std::cout << "start down" << std::endl;
        // TODO: disable gravity?
        if (contact > 0) {
            direction = Direction::Down;
        }
        // Body->SetLinearVelocity(b2Vec2(0, -5));
    }

    void Box::stopMove()
    {
        std::cout << "stop" << std::endl;
        direction = Direction::Stopped;
    }

    void Box::startJump()
    {
        if (contact > 0) {
            jumpStepsLeft = 8;
        }
    }

    void Box::move()
    {
        b2Vec2 velocity = Body->GetLinearVelocity();
        switch (direction)
        {
            case Direction::Left :
                velocity = b2Vec2(-5, velocity.y);
            break;
            case Direction::Right :
                velocity = b2Vec2(5, velocity.y);
            break;
            case Direction::Up :
                velocity = b2Vec2(0, -5);
            break;
            case Direction::Down :
                velocity = b2Vec2(0, 5);
            break;
            case Direction::Stopped :
                if (contact > 0) {
                    velocity = b2Vec2(0, velocity.y);
                }
            break;
        }
        Body->SetLinearVelocity(velocity);

        // Other possible ways of moving around:
        //apply gradual force upwards
        // Body->ApplyForce(b2Vec2(10 ,10), Body->GetWorldCenter(), true);
        //apply immediate force upwards
        // Body->ApplyLinearImpulse(b2Vec2(10, 10), Body->GetWorldCenter(), true);
        //teleport or 'warp' to new location
        // Body->SetTransform( b2Vec2(10,20), 0);
    }

    void Box::jump()
    {
        if (jumpStepsLeft > 0)
        {
            std::cout << "jump: " << jumpStepsLeft << std::endl;
            Body->ApplyForce(b2Vec2(0, -50), Body->GetWorldCenter(), true);
            jumpStepsLeft--;
        }
    }
}
