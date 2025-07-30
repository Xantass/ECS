#include "MovementSystem.hpp"
#include "Registry.hpp"

void MovementSystem::OnUpdate()
{
    auto& dt = registry->getSingleton<DeltaTime>();
    registry->ForEach<Position, Velocity>([&](Entity /*entity*/, Position& pos, Velocity& vel) {
        pos.x += vel.dx * dt.deltaTime;
        pos.y += vel.dy * dt.deltaTime;
    });
}