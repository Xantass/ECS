#include "GravitySystem.hpp"

void GravitySystem::update(Registry &registry, float dt)
{
    // std::cout << "GravitySystem: " << entities.size() << std::endl;
    auto entitiesCopy = entities;
    for (auto entity : entitiesCopy)
    {
        auto &vel = registry.getComponent<Velocity>(entity);
        auto &gravity = registry.getComponent<Gravity>(entity);

        vel.dy += gravity.gravity * dt;
        // std::cout << "vel.dy: " << vel.dy << std::endl;
    }
}