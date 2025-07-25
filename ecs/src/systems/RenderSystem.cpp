#include "RenderSystem.hpp"

void RenderSystem::update(Registry &registry, float /*dt*/)
{
    auto entitiesCopy = entities;
    for (auto entity : entitiesCopy)
    {
        // std::cout << "RenderSystem: " << entity << std::endl;
        auto &pos = registry.getComponent<Position>(entity);
        auto &sprite = registry.getComponent<Sprite>(entity);

        DrawTextureEx(
            sprite.texture,
            {pos.x, pos.y},
            0.0f,
            sprite.scale,
            WHITE);
    }
}