#include <vector>
#include <iostream>
#include <algorithm>

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

/*
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
*/

class MatchOddName {
    public:
        bool operator() (Animal x) const {
            return (x.name.length() % 2) != 0;
        }
};

int main() {
    vector<Animal> zoo {
        {"Snake", "Sid", 0},
        {"Lion", "Simba", 4},
        {"Dog", "Tim", 4},
        {"Dog", "Fido", 4},
        {"Gorilla", "King Kong", 2},
        {"Mouse", "Mikey Mouse", 2},
        {"Sheep", "Dolly", 4}
    };

    cout << "Here is the Zoo:" << endl;
    for (auto animal : zoo) {
        cout << animal;
    }

    vector<Animal> oddNames(zoo.size());
    copy_if(zoo.begin(), zoo.end(), oddNames.begin(), MatchOddName());

    cout << "the odd names" << endl;

    for (auto animal : oddNames) {
        cout << animal;
    }

    vector<Animal> evenLambda;
    copy_if(zoo.begin(), zoo.end(), back_inserter(evenLambda), [](Animal const &x) {return (x.name.length() % 2) == 0;});
    // evenLambda.shrink_to_fit();

    cout << "the even lambda names" << endl;

    for (auto animal : evenLambda) {
        cout << animal;
    }

    return 0;
}
