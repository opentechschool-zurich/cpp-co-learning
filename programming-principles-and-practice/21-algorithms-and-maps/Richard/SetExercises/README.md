# Sample code for sets

# To Run:

``` bash
git clone git@github.com:opentechschool-zurich/cpp-co-learning.git
cd programming-principles-and-practice/21-algorithms-and-maps/Richard/SetExercises
mkdir build
cd build
cmake ..
make
./SetExercises
```

# Results
```
Here is the Zoo:
Animal: Sid Species: Snake Legs: 0
Animal: Simba Species: Lion Legs: 4
Animal: Tim Species: Dog Legs: 4
Animal: Fido Species: Dog Legs: 4
Animal: King Kong Species: Gorilla Legs: 2
Animal: Mikey Mouse Species: Mouse Legs: 2
Animal: Dolly Species: Sheep Legs: 4

A function object to find_if to find King Kong in the Zoo:
We found King Kong: Animal: King Kong Species: Gorilla Legs: 2

A lambda find_if to find the lion in the Zoo:
We found the lion: Animal: Simba Species: Lion Legs: 4

Our zoo has 20 legs

Creating a map from our zoo:
Animal Fido not inserted because animal Animal: Tim Species: Dog Legs: 4
already has the key

zooMap contains:
Key: Dog        Animal: Tim Species: Dog Legs: 4
Key: Gorilla    Animal: King Kong Species: Gorilla Legs: 2
Key: Lion       Animal: Simba Species: Lion Legs: 4
Key: Mouse      Animal: Mikey Mouse Species: Mouse Legs: 2
Key: Sheep      Animal: Dolly Species: Sheep Legs: 4
Key: Snake      Animal: Sid Species: Snake Legs: 0

Creating a multipmap from our zoo:                                                                                       zooMultimap contains:                                                                                                          Key: Dog        Animal: Tim Species: Dog Legs: 4                                                                               Key: Dog        Animal: Fido Species: Dog Legs: 4
Key: Gorilla    Animal: King Kong Species: Gorilla Legs: 2
Key: Lion       Animal: Simba Species: Lion Legs: 4
Key: Mouse      Animal: Mikey Mouse Species: Mouse Legs: 2
Key: Sheep      Animal: Dolly Species: Sheep Legs: 4
Key: Snake      Animal: Sid Species: Snake Legs: 0
```
