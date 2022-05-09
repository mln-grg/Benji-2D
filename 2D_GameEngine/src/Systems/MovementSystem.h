#pragma once
#include "../ECS/ECS.h"
#include "../Component/TransformComponent.h"
#include "../Component/RigidBodyComponent.h"

class MovementSystem : public System {
public:
    MovementSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void Update(double deltaTime) {
        // Loop all entities that the system is interested in
        for (auto entity : GetSystemEntities()) {
            // Update entity position based on its velocity
            auto& transform = entity.GetComponent<TransformComponent>();
            const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

            transform.position.x += rigidbody.velocity.x * deltaTime;
            transform.position.y += rigidbody.velocity.y * deltaTime;

            Logger::Log(
                "Entity id = " +
                std::to_string(entity.GetId()) +
                " position is now (" +
                std::to_string(transform.position.x) +
                ", " +
                std::to_string(transform.position.y) + ")"
            );
        }
    }
};

