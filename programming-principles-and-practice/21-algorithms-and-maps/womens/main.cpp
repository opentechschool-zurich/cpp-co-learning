#include <list>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

// create a class for an Animal
struct Animal {
public:
    string species;
    string name;
    int legs;
};

// override the << operator so that we can just cout << animal
ostream& operator<<(ostream& os, const Animal& referencedAnimal)
{
    os << "Animal: " << referencedAnimal.name
        << " Species: " << referencedAnimal.species
        << " Legs: " << referencedAnimal.legs << endl;
    return os;
}

// a Function object that compares an animal name
class MatchAnimalName {
    string  storedNameToMatch;
public:
    // store the argument
    MatchAnimalName( string nameToMatch ) : storedNameToMatch( nameToMatch ) { }
    bool operator()( Animal x ) const {
        return x.name == storedNameToMatch;
    }
};


// accumulator function for legs
int legsAccumulator(int priorCount, const Animal& a) {
    return priorCount + a.legs;
}

int countCharacterAnimal(const Animal& an){
    return an.name.size();
}

int main() {
    list<Animal> Zoo {
        {"Snake", "Sid", 0},
        {"Lion", "Simba", 4},
        {"Dog", "Tim", 4},
        {"Dog", "Fido", 4},
        {"Gorilla", "King Kong", 2},
        {"Mouse", "Mikey Mouse", 2},
        {"Sheep", "Dolly", 4}
    };

    
    cout << "Here is the Zoo:" << endl;
    for (auto animal : Zoo) {
        cout << animal;
    }

    cout << endl << "A function object to find_if to find King Kong in the Zoo:" << endl;
    auto foundIterator = find_if( Zoo.begin(), Zoo.end(), MatchAnimalName("King Kong") );
    if ( foundIterator != Zoo.end() ) {
        cout << "We found King Kong: " << *foundIterator;
    }else {
        cout << "We did not find King Kong." << endl;
    }


     cout << endl << "A lambda find_if to find the lion in the Zoo:" << endl;
     auto foundLionIterator = find_if( Zoo.begin(), Zoo.end(),
        [](const Animal& a) -> bool { return a.species == "Lion"; } );
     if ( foundLionIterator != Zoo.end() ) {
         cout << "We found the lion: " << *foundLionIterator;
     } else {
         cout << "We did not find the lion." << endl;
    }


    cout << endl << "Our zoo has "
        << accumulate( Zoo.begin(), Zoo.end(), 0, legsAccumulator)
        << " legs" << endl << endl;


    cout << "Creating a map from our zoo: " << endl;
    map<string, Animal> zooMap;
    // manually copy the animals into the map with the key as species:
    for ( auto animal : Zoo ) {
        auto returnIterator = zooMap.insert( pair<string,Animal> (animal.species, animal) );
        if ( returnIterator.second == false ) {
            cout << "Animal " << animal.name << " not inserted because animal "
                << returnIterator.first->second
                << "already has the key" << endl;
        }
    }
    cout << endl << "zooMap contains:" << endl;
    for ( auto element : zooMap ) {
        cout << "Key: " << element.first << "\t" << element.second;
    }


    cout << endl << "Creating a multipmap from our zoo: " << endl;
    multimap<string, Animal> zooMultimap;
    // manually copy the animals into the map with the key as species:
    for ( auto animal : Zoo ) {
        auto returnIterator = zooMultimap.insert( pair<string,Animal> (animal.species, animal) );
    }
    cout << "zooMultimap contains:" << endl;
    for ( auto element : zooMultimap ) {
        cout << "Key: " << element.first << "\t" << element.second;
    }

    cout << "\nNumber of Chars in Animal: " << endl;
    for(auto animal: Zoo) {
    cout << animal.name << " has " << countCharacterAnimal(animal) << " Chars" << endl;
    }
    return 0;
}
