#include "CooldownSystem.hpp"
#include "Registry.hpp"

void CooldownSystem::OnUpdate()
{
    auto& dt = registry->getSingleton<DeltaTime>();
    registry->ForEach<Cooldown>([&](Entity /*entity*/, Cooldown& cooldown) {
        cooldown.timer += dt.deltaTime;
    });
}