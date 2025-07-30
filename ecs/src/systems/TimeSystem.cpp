#include "TimeSystem.hpp"
#include "DeadEvent.hpp"

void TimeSystem::update(Registry& registry, float dt)
{
    auto entitiesCopy = entities;
    for (auto entity : entitiesCopy)
    {
        auto &time = registry.getComponent<Time>(entity);
        time.time -= dt;
        if (time.time <= 0)
        {
            registry.getEventBus().emit(DeadEvent{entity});
        }
    }
}