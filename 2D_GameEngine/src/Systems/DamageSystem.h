#pragma once
#include "../ECS/ECS.h"
#include "../Component/BoxColliderComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class DamageSystem: public System {
    public:
        DamageSystem() {
            RequireComponent<BoxColliderComponent>();
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
        }

        void OnCollision(CollisionEvent& event) {
            std::string aId = std::to_string(event.a.GetId());
            std::string bId = std::to_string(event.b.GetId());
            Logger::Log("Collision event emitted: " + aId + " and " + bId);
            
            //event.a.Kill();
            //event.b.Kill();
        }

        void Update() {

        }
};

