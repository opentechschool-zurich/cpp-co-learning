#include <iostream>
#include "world/polygon.h"
#include "game.h"

namespace Box2DRolling {
    Polygon::Polygon(b2World* world, int x, int y)
    {
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x/scale, y/scale);
        BodyDef.type = b2_staticBody;
        b2Body* Body = world->CreateBody(&BodyDef);

        Body->SetUserData(this);

		b2Vec2 vertices[5];
		vertices[0].Set(x/scale -1,  y/scale +2);
		vertices[1].Set(x/scale -1,  y/scale +0);
		vertices[2].Set(x/scale +0,  y/scale -3);
		vertices[3].Set(x/scale +1,  y/scale +0);
		vertices[4].Set(x/scale +1,  y/scale +1);

        b2FixtureDef FixtureDef;

		b2PolygonShape polygonShape;
		polygonShape.Set(vertices, 5);
		FixtureDef.shape = &polygonShape; //change the shape of the fixture
        FixtureDef.density = 0.f;
		Body->CreateFixture(&FixtureDef);
    }

    void Polygon::render(sf::RenderWindow* window, b2Body* body)
    {
		b2Fixture* fixture = body->GetFixtureList();
        if (fixture)
        {
            b2Shape* shape = fixture->GetShape();
            if (shape->GetType() == b2Shape::Type::e_polygon)
            {
                b2PolygonShape* shapePolygon = dynamic_cast<b2PolygonShape*>(shape);
                // std::cout << shapePolygon->GetVertexCount() << std::endl;
                sf::ConvexShape polygon;
                polygon.setPointCount(shapePolygon->GetVertexCount());
                for (int i = 0; i < shapePolygon->GetVertexCount(); i++)
                {
                    b2Vec2 shapeVertex = shapePolygon->GetVertex(i);
                    sf::Vector2f vertex(shapeVertex.x * scale, shapeVertex.y * scale);
                    polygon.setPoint(i, vertex);
                }
                polygon.setFillColor(sf::Color(50,50,250));
                polygon.setOutlineColor(sf::Color::Red);
                polygon.setOutlineThickness(5);
                polygon.setPosition(body->GetWorldCenter().x * scale - width /2, body->GetWorldCenter().y * scale - height /2);
                polygon.setPosition(body->GetWorldCenter().x * scale - width, body->GetWorldCenter().y * scale - height);
                window->draw(polygon);
            }
            
        }
    }
}
