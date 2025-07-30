#include "BulletSystem.hpp"

void BulletSystem::update(Registry &registry, float /*dt*/)
{
    auto entitiesCopy = entities;
    for (auto entity : entitiesCopy)
    {
        // std::cout << "BulletSystem: " << entity << std::endl;
        auto &pos = registry.getComponent<Position>(entity);
        // auto &bullet = registry.getComponent<Bullet>(entity);

        if (pos.x > GetScreenWidth() || pos.x < 0 || pos.y > GetScreenHeight() || pos.y < 0)
        {
            // std::cout << "Bullet destroyed" << std::endl;
            registry.destroyEntity(entity);
            continue;
        }
    }
}