#include "RenderSystem.hpp"

void RenderSystem::update(Registry &registry, float /*dt*/)
{
    auto entitiesCopy = entities;
    for (auto entity : entitiesCopy)
    {
        // std::cout << "RenderSystem: " << entity << std::endl;
        auto &pos = registry.getComponent<Position>(entity);
        auto &sprite = registry.getComponent<Sprite>(entity);

        Rectangle src = { (float)sprite.frame.x, (float)sprite.frame.y, (float)sprite.frame.width, (float)sprite.frame.height };
        Rectangle dst = { pos.x, pos.y, (float)sprite.frame.width * SCALE, (float)sprite.frame.height * SCALE };
        DrawTexturePro(sprite.texture, src, dst, {0, 0}, sprite.frame.rotated, WHITE);
        // DrawTextureEx(
        //     sprite.texture,
        //     {pos.x, pos.y},
        //     0.0f,
        //     sprite.scale,
        //     WHITE);
    }
}