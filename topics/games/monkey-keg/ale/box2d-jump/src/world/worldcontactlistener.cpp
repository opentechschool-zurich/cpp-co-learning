#include "world/worldcontactlistener.h"
#include "world/worlditem.h"

namespace Box2DJump {
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
