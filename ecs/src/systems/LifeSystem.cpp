#include "LifeSystem.hpp"
#include "Registry.hpp"

void LifeSystem::OnUpdate()
{
    auto& eventBus = registry->getEventBus();
    registry->ForEach<Health>([&](Entity entity, Health& health) {
        if (health.health <= 0) {
            eventBus.emit(DeadEvent{entity});
        }
    });
}