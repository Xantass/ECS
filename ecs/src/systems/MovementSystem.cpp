#include "MovementSystem.hpp"

void MovementSystem::update(Registry &registry, float dt)
{
    auto entitiesCopy = entities;
    for (auto entity : entitiesCopy)
    {
        // std::cout << "MovementSystem: " << entity << std::endl;
        auto &pos = registry.getComponent<Position>(entity);
        auto &vel = registry.getComponent<Velocity>(entity);
        pos.x += vel.dx * dt;
        pos.y += vel.dy * dt;
    }
}