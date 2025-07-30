#include "RenderSystem.hpp"
#include "Registry.hpp"

void RenderSystem::OnUpdate()
{
    // std::cout << "RenderSystem" << std::endl;
    registry->ForEach<Position, Sprite>([](Entity /*entity*/, Position& pos, Sprite& sprite) {
        // std::cout << "RenderSystem entity: " << entity << std::endl;
        Rectangle src = { (float)sprite.frame.x, (float)sprite.frame.y, (float)sprite.frame.width, (float)sprite.frame.height };
        Rectangle dst = { pos.x, pos.y, (float)sprite.frame.width * SCALE, (float)sprite.frame.height * SCALE };
        DrawTexturePro(sprite.texture, src, dst, {0, 0}, sprite.frame.rotated, WHITE);
    });
    // std::cout << "RenderSystem end" << std::endl;
}