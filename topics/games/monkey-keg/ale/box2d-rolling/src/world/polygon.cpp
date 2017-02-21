#include <iostream>
#include <string>
#include "world/polygon.h"
#include "game.h"

namespace Box2DRolling {
    /**
     * @param int x sfml screen coordinates
     * @param int y sfml screen coordinates
     */
    Polygon::Polygon(b2World* world, int x, int y)
    {
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x/scale, y/scale);
        BodyDef.type = b2_staticBody;
        b2Body* Body = world->CreateBody(&BodyDef);

        Body->SetUserData(this);

		b2Vec2 vertices[5];
        /*
		vertices[0].Set(x/scale -1,  y/scale +2);
		vertices[1].Set(x/scale -1,  y/scale +0);
		vertices[2].Set(x/scale +0,  y/scale -3);
		vertices[3].Set(x/scale +1,  y/scale +0);
		vertices[4].Set(x/scale +1,  y/scale +1);
        */
        // Polygon* polygon = new Polygon(&world, 150.f, 150.f);
		vertices[0].Set((x - 100)/scale,( y + 200)/scale);
		vertices[1].Set((x - 100)/scale,( y + 0  )/scale);
		vertices[2].Set((x + 0  )/scale,( y - 300)/scale);
		vertices[3].Set((x + 100)/scale,( y + 0  )/scale);
		vertices[4].Set((x + 100)/scale,( y + 100)/scale);

        b2FixtureDef FixtureDef;

		b2PolygonShape polygonShape;
		polygonShape.Set(vertices, 5);
		FixtureDef.shape = &polygonShape; //change the shape of the fixture
        FixtureDef.density = 0.f;
		Body->CreateFixture(&FixtureDef);
		std::cout << "world center x" << Body->GetWorldCenter().x * scale << std::endl;
		std::cout << "world center y" << Body->GetWorldCenter().y * scale << std::endl;
    }

    void Polygon::render(sf::RenderWindow* window, b2Body* body)
    {
		b2Fixture* fixture = body->GetFixtureList();
        sf::Font font;
        font.loadFromFile("assets/Franchise-Bold-hinted.ttf");
        sf::Text text;
        text.setFont(font);
		text.setCharacterSize(24); // in pixels, not points!
		text.setFillColor(sf::Color::Black);
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
                // polygon.setFillColor(sf::Color(50,50,250));
                polygon.setOutlineColor(sf::Color::Red);
                polygon.setOutlineThickness(5);
                polygon.setPosition(body->GetWorldCenter().x * scale, body->GetWorldCenter().y * scale);
                window->draw(polygon);

				sf::Vector2f position = polygon.getPosition();
                for (int i = 0; i < polygon.getPointCount(); i++)
                {
                    sf::Vector2f vertex = polygon.getPoint(i);
                    text.setString(std::to_string(i));
                    text.setPosition(position.x + vertex.x, position.y + vertex.y);
                    window->draw(text);
                }
				text.setString("[*]");
				text.setPosition(position.x, position.y);
				window->draw(text);
            }
        }
    }
}
