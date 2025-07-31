#include "RenderSystem.hpp"
#include "Registry.hpp"

void RenderSystem::OnUpdate()
{
    // std::cout << "RenderSystem" << std::endl;

    const int cellSize = 64;
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    for (int x = 0; x < screenWidth; x += cellSize) {
        DrawLine(x, 0, x, screenHeight, {0, 255, 0, 120});
    }
    for (int y = 0; y < screenHeight; y += cellSize) {
        DrawLine(0, y, screenWidth, y, {0, 255, 0, 120});
    }

    registry->ForEach<Position, Sprite>([](Entity /*entity*/, Position& pos, Sprite& sprite) {
        // std::cout << "RenderSystem entity: " << entity << std::endl;
        Rectangle src = { (float)sprite.frame.x, (float)sprite.frame.y, (float)sprite.frame.width, (float)sprite.frame.height };
        Rectangle dst = { pos.x, pos.y, (float)sprite.frame.width * SCALE, (float)sprite.frame.height * SCALE };
        DrawTexturePro(sprite.texture, src, dst, {0, 0}, sprite.frame.rotated, WHITE);
    });
    // std::cout << "RenderSystem end" << std::endl;
}