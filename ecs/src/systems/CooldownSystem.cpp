#include "CooldownSystem.hpp"

void CooldownSystem::update(Registry &registry, float dt)
{
    // std::cout << "CooldownSystem: " << entities.size() << std::endl;
    auto entitiesCopy = entities;
    for (auto entity : entitiesCopy)
    {
        auto &cooldown = registry.getComponent<Cooldown>(entity);
        cooldown.timer += dt;
    }
}