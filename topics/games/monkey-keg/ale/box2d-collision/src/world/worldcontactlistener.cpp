#include "world/worldcontactlistener.h"
#include "world/worlditem.h"
#include <iostream>
#include <algorithm>

namespace Box2DCollisions {

    WorldContactListener::WorldContactListener() {
        if (!boxCrashSoundBuffer.loadFromFile("assets/box-crash.ogg"))
            std::cout << "Failed to load sound file assets/box-crash.ogg\n";
    }


    void WorldContactListener::BeginContact(b2Contact* contact)
    {
        void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData)
        {
            static_cast<WorldItem*>(bodyUserData)->startContact();
        }

        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData)
        {
            static_cast<WorldItem*>(bodyUserData)->startContact();
        }

        playingSounds.emplace_back(boxCrashSoundBuffer);
        playingSounds.back().play();
        std::remove_if(playingSounds.begin(), playingSounds.end(), [](sf::Sound sound) {return sound.getStatus() == sf::Sound::Stopped;});
    }

    void WorldContactListener::EndContact(b2Contact* contact)
    {
        void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData)
        {
            static_cast<WorldItem*>(bodyUserData)->endContact();
        }

        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData)
        {
            static_cast<WorldItem*>(bodyUserData)->endContact();
        }
    }
}
