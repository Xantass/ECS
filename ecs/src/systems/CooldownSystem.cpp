#include "CooldownSystem.hpp"
#include "Registry.hpp"

void CooldownSystem::OnUpdate()
{
    registry->ForEach<Cooldown>([&](Entity /*entity*/, Cooldown& cooldown) {
        cooldown.timer += registry->getSingleton<DeltaTime>().deltaTime;
    });
}