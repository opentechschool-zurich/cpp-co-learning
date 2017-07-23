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

	Customer currentCustomer;
	boolean servingCustomer = false;
	boolean servingDrink = false;
	boolean servingFood = false;
	boolean servingDesert = false;

	sf::Sprite tillSprite;
	sf::Sprite customerSprite;
	sf::Sprite foodSprite;
	sf::Sprite drinkSprite;
	sf::Sprite desertSprite;

	sf::Text text;

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
			if (!BurgerShopQueue.empty()) {
				tills[number].currentCustomer = BurgerShopQueue.front();
				BurgerShopQueue.pop();
				tills[number].servingCustomer = true;
			}
			BurgerShopQueueMutex.unlock();

			if (tills[number].servingCustomer) {
				if (tills[number].currentCustomer.wantsDrink) {
					tills[number].servingDrink = true;
					std::stringstream ss;
					ss << "Cust: " << tills[number].currentCustomer.id << " serving Drink";
					tills[number].text.setString(ss.str());
					std::this_thread::sleep_for(std::chrono::milliseconds(50 + rand() % 600));
				}
				if (tills[number].currentCustomer.wantsFood) {
					tills[number].servingFood = true;
					std::stringstream ss;
					ss << "Cust: " << tills[number].currentCustomer.id << " serving Food";
					tills[number].text.setString(ss.str());
					std::this_thread::sleep_for(std::chrono::milliseconds(50 + rand() % 600));
				}
				if (tills[number].currentCustomer.wantsDesert) {
					tills[number].servingDesert = true;
					std::stringstream ss;
					ss << "Cust: " << tills[number].currentCustomer.id << " serving Desert";
					tills[number].text.setString(ss.str());
					std::this_thread::sleep_for(std::chrono::milliseconds(50 + rand() % 600));
				}
				tills[number].text.setString("next, please!");
				tills[number].servingCustomer = false;
				tills[number].servingFood = false;
				tills[number].servingDrink = false;
				tills[number].servingDesert = false;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(200 + rand() % 300));
		if (!tills[number].open) {
			tills[number].text.setString("closed");
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
	sf::Texture customerTexture;
	customerTexture.loadFromFile("customer.png");
	sf::Texture foodTexture;
	foodTexture.loadFromFile("food.png");
	sf::Texture drinkTexture;
	drinkTexture.loadFromFile("drink.png");
	sf::Texture desertTexture;
	desertTexture.loadFromFile("desert.png");

	std::thread produceCustomers(produceCustomers);
	std::vector<std::thread> counters;
	for (byte i = 0; i < MAX_COUNTERS; ++i) {
		counters.push_back(std::thread(serveCustomers, i));
		sf::Sprite tillSprite;
		tillSprite.setTexture(tillGreyTexture, true);
		tillSprite.setPosition(TILL_X + 200, TILL_HEIGHT * i + 50);
		tills[i].tillSprite = tillSprite;

		sf::Sprite customerSprite;
		customerSprite.setTexture(customerTexture, true);
		customerSprite.setPosition(TILL_X, TILL_HEIGHT * i + 50);
		tills[i].customerSprite = customerSprite;

		sf::Sprite foodSprite;
		foodSprite.setTexture(foodTexture, true);
		foodSprite.setPosition(TILL_X + 45, TILL_HEIGHT * i + 60);
		tills[i].foodSprite = foodSprite;

		sf::Sprite drinkSprite;
		drinkSprite.setTexture(drinkTexture, true);
		drinkSprite.setPosition(TILL_X + 90, TILL_HEIGHT * i + 40);
		tills[i].drinkSprite = drinkSprite;

		sf::Sprite desertSprite;
		desertSprite.setTexture(desertTexture, true);
		desertSprite.setPosition(TILL_X + 105, TILL_HEIGHT * i + 50);
		tills[i].desertSprite = desertSprite;

		tills[i].text.setFont(font);
		tills[i].text.setCharacterSize(30);
		tills[i].text.setColor(sf::Color::White);
		tills[i].text.setStyle(sf::Text::Bold);
		tills[i].text.setPosition(TILL_X, TILL_HEIGHT * i);
		tills[i].text.setString("nobody");
	}

	sf::RenderWindow window(sf::VideoMode(850, 700), "Burger Shop Queue");

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
					if (event.mouseButton.x > TILL_X + 200 && event.mouseButton.x < TILL_X + TILL_WIDTH + 200
						&& event.mouseButton.y > TILL_HEIGHT * i && event.mouseButton.y < TILL_HEIGHT * (i + 1)) {
						tills[i].open = !tills[i].open;
						tills[i].tillSprite.setTexture(tills[i].open ? tillColoredTexture : tillGreyTexture);
					}
				}
			}
		}

		window.clear();
		queueCount.setString(std::to_string(BurgerShopQueue.size()));
		window.draw(queueLabel);
		window.draw(queueCount);
		for (byte i = 0; i < MAX_COUNTERS; ++i) {
			window.draw(tills[i].tillSprite);
			window.draw(tills[i].text);
			if (tills[i].servingCustomer) {
				window.draw(tills[i].customerSprite);
			}
			if (tills[i].servingFood) {
				window.draw(tills[i].foodSprite);
			}
			if (tills[i].servingDrink) {
				window.draw(tills[i].drinkSprite);
			}
			if (tills[i].servingDesert) {
				window.draw(tills[i].desertSprite);
			}
		}
		window.display();
	}
	return 0;
}