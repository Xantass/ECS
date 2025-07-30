#include "UiSystem.hpp"

void UiSystem::update(Registry& registry, float dt)
{
    auto entitiesCopy = entities;
    for (auto entity : entitiesCopy)
    {
        // auto &pos = registry.getComponent<Position>(entity);
        // auto &vel = registry.getComponent<Velocity>(entity);
        // pos.x += vel.dx * dt;
        // pos.y += vel.dy * dt;
    }
}