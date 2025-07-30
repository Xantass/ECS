#include "MovementSystem.hpp"
#include "Registry.hpp"

void MovementSystem::OnUpdate()
{
    registry->ForEach<Position, Velocity>([&](Entity /*entity*/, Position& pos, Velocity& vel) {
        // std::cout << "MovementSystem entity: " << entity << std::endl;
        // std::cout << "Entity pos.x before: " << pos.x << std::endl;
        // std::cout << "Entity pos.y before: " << pos.y << std::endl;
        pos.x += vel.dx * registry->getSingleton<DeltaTime>().deltaTime;
        pos.y += vel.dy * registry->getSingleton<DeltaTime>().deltaTime;
        // std::cout << "Entity pos.x after: " << pos.x << std::endl;
        // std::cout << "Entity pos.y after: " << pos.y << std::endl;
    });
}