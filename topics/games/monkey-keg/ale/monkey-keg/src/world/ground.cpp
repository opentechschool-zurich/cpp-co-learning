#include <iostream>
#include <cmath>
#include "world/ground.h"
#include "game.h"

/**
 * TODO:
 * - rename ground as floor
 */

namespace MonkeyKeg {
    /*
     * @brief create a floor/ground with start coordinate, length and angle
     */
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
     * @brief create a floor/ground with start and end pixel coordinates
     */
    Ground::Ground(b2World* world, b2Vec2 start, b2Vec2 end)
    {
        std::cout << start.x << std::endl;
        length = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));
        float angle = std::atan2(end.y - start.y, end.x - start.x);
        std::cout << "length: " << length << std::endl;
        // std::cout << "angle: " << angle * radtodeg << std::endl;
        std::cout << "angle: " << angle << std::endl;

        // c2 = a2 + b2
        auto middle = b2Vec2((start.x + end.x) / 2, (start.y + end.y) / 2);

        b2BodyDef BodyDef;
        // TODO: check support of std::experimental::optional...
        // (for which project was it?)
        // TODO: probably, we have to use the middle point
        // BodyDef.position = b2Vec2(start.x/scale, start.y/scale);
        BodyDef.position = b2Vec2(middle.x/scale, middle.y/scale);
        BodyDef.type = b2_staticBody;
        b2Body* Body = world->CreateBody(&BodyDef);

        Body->SetUserData(this);

        b2PolygonShape Shape;
        Body->SetTransform(Body->GetWorldCenter(), angle);
        // TODO: can SetAsBox directly use x/y?
        Shape.SetAsBox((length/2)/scale, (height/2)/scale);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 0.f;
        FixtureDef.shape = &Shape;
        Body->CreateFixture(&FixtureDef);
    }

    void Ground::render(sf::RenderWindow* window, b2Body* body)
    {

        int x = scale * body->GetPosition().x;
        int y = scale * body->GetPosition().y;

        // int x =  100;
        // int y =  100;

        /*
        sf::Font font;
        font.loadFromFile("assets/Franchise-Bold-hinted.ttf");
        sf::Text text;
        text.setFont(font);
		text.setCharacterSize(24); // in pixels, not points!
		text.setFillColor(sf::Color::Black);

        text.setString("s <------");
        text.setPosition(x , y);
        window->draw(text);
        */

        sf::RectangleShape rectangle(sf::Vector2f(length, height));
        rectangle.setFillColor(sf::Color(50,50,250));

        rectangle.setOrigin(length/2, height/2);
        rectangle.setPosition(scale * body->GetPosition().x, scale * body->GetPosition().y);
        rectangle.setRotation(body->GetAngle() * radtodeg);

        window->draw(rectangle);
    }
}
