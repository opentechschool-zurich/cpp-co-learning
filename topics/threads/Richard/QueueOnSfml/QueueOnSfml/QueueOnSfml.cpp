// QueueOnSfml.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>   
#include <chrono>
#include <thread>
#include <queue>
#include <mutex>
#include <Windows.h>

const byte MAX_COUNTERS = 3;

boolean openTill[MAX_COUNTERS];

class Customer {
private:
	static int next_id;
public:
	Customer()
	{
		id = Customer::next_id++;
		wantsDrink = rand() % 2;
		wantsFood = rand() % 2;
		wantsDesert = rand() % 2;
	}

	bool wantsDrink;
	bool wantsFood;
	bool wantsDesert;
	int id;

	void describe() {
		std::cout << "I am customer " << id << " and I " << (wantsDrink ? " am thirsty " : " am not thirsty ") <<
			(wantsFood ? " am hungry " : " am not hungry ") <<
			(wantsDesert ? " and have a sweet tooth " : " don't feel like desert")
			<< std::endl;
	}
};

int Customer::next_id = 0;

std::queue<Customer> BurgerShopQueue;
std::mutex BurgerShopQueueMutex;

void produceCustomers() {
	while (true) {
		Customer cust;
		cust.describe();
		BurgerShopQueueMutex.lock();
		BurgerShopQueue.push(cust);
		BurgerShopQueueMutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(200 + rand() % 300));
	}
}

void serveCustomers(byte number) {
	while (true) {
		if (openTill[number]) {
			BurgerShopQueueMutex.lock();
			if (!BurgerShopQueue.empty()) {
				auto cust = BurgerShopQueue.front();
				BurgerShopQueue.pop();
				cust.describe();
			}
			BurgerShopQueueMutex.unlock();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(200 + rand() % 600));
	}
}


int main()
{
	srand(time(0));

	const int TILL_X = 370;
	const int TILL_WIDTH = 200;
	const int TILL_HEIGHT = 140;
	sf::Texture tillColoredTexture;
	tillColoredTexture.loadFromFile("till.png");
	sf::Texture tillGreyTexture;
	tillGreyTexture.loadFromFile("tillGrey.png");

	std::thread produceCustomers(produceCustomers);
	std::vector<std::thread> counters;
	std::vector<sf::Sprite> tills;
	for (byte i = 0; i < MAX_COUNTERS; ++i) {
		openTill[i] = false;
		counters.push_back(std::thread(serveCustomers, i));
		sf::Sprite sprite;
		sprite.setTexture(tillGreyTexture, true);
		sprite.setPosition(TILL_X, TILL_HEIGHT * i);
		tills.push_back(sprite);
	}

	sf::RenderWindow window(sf::VideoMode(700, 500), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Font font;
	if (!font.loadFromFile("Abel-Regular.ttf"))
	{
		std::cerr << "Could not load Abel-Regular.ttf\n";
		exit(255);
	}

	sf::Text queueLabel;
	queueLabel.setFont(font);
	queueLabel.setString("Queue count");
	queueLabel.setCharacterSize(48);
	queueLabel.setColor(sf::Color::White);
	queueLabel.setStyle(sf::Text::Bold);
	queueLabel.setPosition(100, 20);

	sf::Text queueCount;
	queueCount.setFont(font);
	queueCount.setCharacterSize(48);
	queueCount.setColor(sf::Color::White);
	queueCount.setStyle(sf::Text::Bold);
	queueCount.setPosition(160, 80);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				for (byte i = 0; i < MAX_COUNTERS; ++i) {
					if (event.mouseButton.x > TILL_X && event.mouseButton.x < TILL_X + TILL_WIDTH
						&& event.mouseButton.y > TILL_HEIGHT * i && event.mouseButton.y < TILL_HEIGHT * (i + 1)) {
						std::cout << "till " << i << "was pressed" << std::endl;
						openTill[i] = !openTill[i];
						tills.at(i).setTexture(openTill[i] ? tillColoredTexture : tillGreyTexture);
					}
				}
			}
		}

		window.clear();
		queueCount.setString(std::to_string(BurgerShopQueue.size()));
		window.draw(queueLabel);
		window.draw(queueCount);
		for (auto sprite : tills) {
			window.draw(sprite);
		}
		window.display();
	}
	return 0;
}

