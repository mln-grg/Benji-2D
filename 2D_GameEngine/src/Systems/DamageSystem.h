#pragma once
#include "../ECS/ECS.h"
#include "../Component/BoxColliderComponent.h"
#include "../Component/ProjectileComponent.h"
#include "../Component/HealthComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class DamageSystem : public System {
public:
    DamageSystem() {
        RequireComponent<BoxColliderComponent>();
    }

    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
        eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
    }

    void OnCollision(CollisionEvent& event) {
        Entity a = event.a;
        Entity b = event.b;
        Logger::Log("Collision event emitted: " + std::to_string(a.GetId()) + " and " + std::to_string(b.GetId()));

        if (a.BelongsToGroup("projectiles") && b.HasTag("player")) {
            OnProjectileHitsPlayer(a, b); // "a" is the projectile, "b" is the player
        }

        if (b.BelongsToGroup("projectiles") && a.HasTag("player")) {
            OnProjectileHitsPlayer(b, a); // "b" is the projectile, "a" is the player
        }

        if (a.BelongsToGroup("projectiles") && b.BelongsToGroup("enemies")) {
            OnProjectileHitsEnemy(a, b); // "a" is the projectile, "b" is the enemy
        }

        if (b.BelongsToGroup("projectiles") && a.BelongsToGroup("enemies")) {
            OnProjectileHitsEnemy(b, a); // "b" is the projectile, "a" is the enemy
        }
    }

    void OnProjectileHitsPlayer(Entity projectile, Entity player) {
        const auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

        if (!projectileComponent.isFriendly) {
            // Reduce the health of the player by the projectile hitPercentDamage
            auto& health = player.GetComponent<HealthComponent>();

            // Subtract the health of the player
            health.healthPercentage -= projectileComponent.hitPercentDamage;

            // Kills the player when health reaches zero
            if (health.healthPercentage <= 0) {
                player.Kill();
            }

            // Kill the projectile
            projectile.Kill();
        }
    }

    void OnProjectileHitsEnemy(Entity projectile, Entity enemy) {
        const auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

        // Only damage the enemy if projectile is friendly
        if (projectileComponent.isFriendly) {
            auto& health = enemy.GetComponent<HealthComponent>();

            // Subtract from enemy health
            health.healthPercentage -= projectileComponent.hitPercentDamage;

            // Kills the enemy if health reaches zero
            if (health.healthPercentage <= 0) {
                enemy.Kill();
            }

            // Destroy projectile
            projectile.Kill();
        }
    }
};

