#include "DebugDrawSystem.hpp"
#include "Registry.hpp"

#define SCALE 4.0f

void DebugDrawSystem::OnUpdate()
{
    auto& debug = registry->getSingleton<Debug>();
    if (!debug.collider)
        return;

    registry->ForEach<Position, Sprite>([&](Entity entity, Position& pos, Sprite& sprite) {
        if (debug.collider) {
            float x = pos.x - (sprite.frame.width * SCALE);
            float y = pos.y;
            std::cout << "Entity: " << entity << std::endl;
            std::cout << "x: " << x << std::endl;
            std::cout << "y: " << y << std::endl;
            std::cout << "sprite.frame.width * SCALE: " << sprite.frame.width * SCALE << std::endl;
            std::cout << "sprite.frame.height * SCALE: " << sprite.frame.height * SCALE << std::endl;
            DrawRectangleLines(x, y, sprite.frame.width * SCALE, sprite.frame.height * SCALE, RED);
        }
    });
}