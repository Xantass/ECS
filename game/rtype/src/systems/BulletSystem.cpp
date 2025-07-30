#include "BulletSystem.hpp"
#include "Registry.hpp"
#include "DeadEvent.hpp"

void BulletSystem::OnUpdate()
{
    registry->ForEach<Position, Bullet>([&](Entity entity, Position& pos, Bullet&) {
        if (pos.x > GetScreenWidth() || pos.x < 0 || pos.y > GetScreenHeight() || pos.y < 0)
        {
            eventBus->emit(DeadEvent{entity});
        }
    });
}