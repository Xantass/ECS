#include "LifeSystem.hpp"
#include "Registry.hpp"

void LifeSystem::OnUpdate()
{
    registry->ForEach<Health>([&](Entity entity, Health& health) {
        if (health.health <= 0) {
            eventBus->emit(DeadEvent{entity});
        }
    });
}