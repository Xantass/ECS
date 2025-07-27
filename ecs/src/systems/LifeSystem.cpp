#include "LifeSystem.hpp"

void LifeSystem::update(Registry& registry, float /*dt*/)
{
    auto entitiesCopy = entities;
    for (auto entity : entitiesCopy)
    {
        auto& health = registry.getComponent<Health>(entity);
        if (health.health <= 0)
        {
            registry.getEventBus().emit(DeadEvent(entity));
        }
    }
}