# QueueOnSfml

A graphical visualisation of a ```std::queue```

Clients enter a burger shop desiring food, drink and desert. They enter a
queue and are then called to any of the open tills to be served.

# Screenshot

![Screenshot](http://opentechschool-zurich.github.io/cpp-co-learning/topics/threads/Richard/QueueOnSfml/screenshot.png)

# Description

This is a single-file C++ program which was written using the Microsoft Visual
Studio 2017 IDE. It uses the SFML library for the graphics.

The program has two classes: a Customer Class and a Till class.
Customers are created by the ```produceCustomers``` function which is started in a
bespoke thread. The function produces a customer and sleeps a short while
before producing the next one. Customers are placed on the queue. The constructor
for the Customer randomly assigns what the customer would want form the
burger shop: ```wantsDrink``` ```wantsFood``` ```wantsDesert```.

Note that in C++ the ```std::queue``` is not thread safe and bad things will happen
if there is a concurrent modification. To prevent this the code uses a ```std::mutex
BurgerShopQueueMutex``` which shall be locked before anything touches the queue and
unlocked afterwards. Calling ```BurgerShopQueueMutex.lock()``` is blocking which means
that the thread will wait until the mutex can be locked before continuing.

The program creates ```MAX_COUNTERS``` number of tills. Each till is represented by
the ```serveCustomers``` function which runs in a bespoke thread. This function
checks if the till is open and if so pulls the customer at the front of the queue.
This is done with the ```!BurgerShopQueue.empty()``` test. The customer is found
with the ```BurgerShopQueue.front()``` statement. But this does not remove the customer
from the queue. That only happens when the ```BurgerShopQueue.pop()``` statement runs.

The ```serveCustomers``` function then updates the state in the ```till[i]``` object and
waits a moment after serving food, drink and desert.

The body of the main function uses rather vanilla SFML to loop over the
eventQueue and draw sprites as per the state in the ```tills[i]``` object. The
```sf::Event::MouseButtonPressed``` event is considered and if the coordinates
match those of a till on the screen the state of the till is toggled.

# Deploy and Running

## Requirements:
Microsoft Visual Studio 2017
SFML

## Set up and linking
What a pain! M$ needs to make this simpler.

Follow the instructions on the SFML page. You need to fix the include directory.

And the linker directory.

Be sure to select the x64 build target as the libraries are otherwise not compatible.

Copy the png images to the target binary directory.

You need to copy the SFML dll libraries (```openal32.dll```
```sfml-audio-2.dll``` ```sfml-audio-d-2.dll``` ```sfml-graphics-2.dll```
```sfml-graphics-d-2.dll``` ```sfml-network-2.dll``` ```sfml-network-d-2.dll```
```sfml-system-2.dll``` ```sfml-system-d-2.dll``` ```sfml-window-2.dll```
```sfml-window-d-2.dll```) to the ```QueueOnSfml\x64\Debug``` directory.

TODO: Improve this description until a newbie can do this too.
