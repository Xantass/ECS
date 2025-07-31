#include "CollisionEvent.hpp"
#include "DeadEvent.hpp"
#include "Bullet.hpp"
#include "Health.hpp"
#include "Registry.hpp"
#include "Enemy.hpp"

void setupReaction(Registry& registry)
{
    registry.getEventBus().subscribe<CollisionEvent>([&](const CollisionEvent& event) {
        std::cout << "CollisionEvent: " << event.entityA << " " << event.entityB << std::endl;
        if (registry.hasComponent<Enemy>(event.entityA) && registry.hasComponent<Bullet>(event.entityB)) {
            auto& health = registry.getComponent<Health>(event.entityA);
            auto& bullet = registry.getComponent<Bullet>(event.entityB);
            health.health -= bullet.damage;
            registry.destroyEntity(event.entityB);
        }
        if (registry.hasComponent<Enemy>(event.entityB) && registry.hasComponent<Bullet>(event.entityA)) {
            auto& health = registry.getComponent<Health>(event.entityB);
            auto& bullet = registry.getComponent<Bullet>(event.entityA);
            health.health -= bullet.damage;
            registry.destroyEntity(event.entityA);
        }
        std::cout << "CollisionEvent: " << event.entityA << " " << event.entityB << " END" << std::endl;
    });
    registry.getEventBus().subscribe<DeadEvent>([&](const DeadEvent& event) {
        // std::cout << "DeadEvent: " << event.entity << std::endl;
        registry.destroyEntity(event.entity);
    });
}