#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>   
#include <chrono>
#include <thread>
#include <queue>
#include <mutex>
#include <Windows.h>
#include <sstream>

const byte MAX_COUNTERS = 3;

class Customer {
private:
	static int next_id;
public:
	Customer() {
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

class Till {
private:
	static int next_id;
public:
	Till()
	{
		id = Till::next_id++;
		open = false;
	}

	bool open;
	int id;
	sf::Sprite sprite;
	sf::Text customer;

	void describe() {
		std::cout << "I am till " << id << " and I am " << (open ? " open " : " closed ")
			<< std::endl;
	}
};

int Till::next_id = 0;

Till tills[MAX_COUNTERS];

std::queue<Customer> BurgerShopQueue;
std::mutex BurgerShopQueueMutex;

void produceCustomers() {
	while (true) {
		Customer cust;
		BurgerShopQueueMutex.lock();
		BurgerShopQueue.push(cust);
		BurgerShopQueueMutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(200 + rand() % 300));
	}
}

void serveCustomers(byte number) {
	while (true) {
		if (tills[number].open) {
			BurgerShopQueueMutex.lock();
			Customer customer;
			boolean gotOne = false;
			if (!BurgerShopQueue.empty()) {
				customer = BurgerShopQueue.front();
				BurgerShopQueue.pop();
				gotOne = true;
			}
			BurgerShopQueueMutex.unlock();

			if (gotOne) {
				if (customer.wantsDrink) {
					std::stringstream ss;
					ss << "Cust: " << customer.id << " serving Drink";
					tills[number].customer.setString(ss.str());
					std::this_thread::sleep_for(std::chrono::milliseconds(50 + rand() % 600));
				}
				if (customer.wantsFood) {
					std::stringstream ss;
					ss << "Cust: " << customer.id << " serving Food";
					tills[number].customer.setString(ss.str());
					std::this_thread::sleep_for(std::chrono::milliseconds(50 + rand() % 600));
				}
				if (customer.wantsDesert) {
					std::stringstream ss;
					ss << "Cust: " << customer.id << " serving Desert";
					tills[number].customer.setString(ss.str());
					std::this_thread::sleep_for(std::chrono::milliseconds(50 + rand() % 600));
				}
				tills[number].customer.setString("next, please!");
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(200 + rand() % 300));
		if (!tills[number].open) {
			tills[number].customer.setString("closed");
		}
	}
}


int main() {
	srand(time(0));

	sf::Font font;
	if (!font.loadFromFile("Abel-Regular.ttf")) {
		std::cerr << "Could not load Abel-Regular.ttf\n";
		exit(255);
	}

	const int TILL_X = 400;
	const int TILL_WIDTH = 200;
	const int TILL_HEIGHT = 210;
	sf::Texture tillColoredTexture;
	tillColoredTexture.loadFromFile("till.png");
	sf::Texture tillGreyTexture;
	tillGreyTexture.loadFromFile("tillGrey.png");

	std::thread produceCustomers(produceCustomers);
	std::vector<std::thread> counters;
	for (byte i = 0; i < MAX_COUNTERS; ++i) {
		counters.push_back(std::thread(serveCustomers, i));
		sf::Sprite sprite;
		sprite.setTexture(tillGreyTexture, true);
		sprite.setPosition(TILL_X, TILL_HEIGHT * i + 50);
		tills[i].sprite = sprite;

		tills[i].customer.setFont(font);
		tills[i].customer.setCharacterSize(30);
		tills[i].customer.setColor(sf::Color::White);
		tills[i].customer.setStyle(sf::Text::Bold);
		tills[i].customer.setPosition(TILL_X, TILL_HEIGHT * i);
		tills[i].customer.setString("nobody");
	}

	sf::RenderWindow window(sf::VideoMode(700, 700), "Burger Shop Queue");

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
						tills[i].open = !tills[i].open;
						tills[i].sprite.setTexture(tills[i].open ? tillColoredTexture : tillGreyTexture);
					}
				}
			}
		}

		window.clear();
		queueCount.setString(std::to_string(BurgerShopQueue.size()));
		window.draw(queueLabel);
		window.draw(queueCount);
		for (byte i = 0; i < MAX_COUNTERS; ++i) {
			window.draw(tills[i].sprite);
			window.draw(tills[i].customer);
		}
		window.display();
	}
	return 0;
}

