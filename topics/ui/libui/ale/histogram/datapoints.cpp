#include "datapoints.h"

#include <random>

Datapoints::Datapoints()
{
	// for a random number you need a seeder, an engine and a distribution
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(0, 100);
	for (int i = 0; i < 10; i++) {
		datapoints.push_back(dist(engine));
    }
}

int Datapoints::get(int i)
{
    return datapoints.at(i);
}

void Datapoints::set(int i, int value)
{
    datapoints.at(i) = value;
}
