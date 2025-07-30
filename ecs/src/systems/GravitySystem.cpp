#include "GravitySystem.hpp"
#include "Registry.hpp"
#include "components/Time.hpp"

void GravitySystem::OnUpdate()
{
    auto& dt = registry->getSingleton<DeltaTime>();
    registry->ForEach<Velocity, Gravity>([&](Entity /*entity*/, Velocity& vel, Gravity& gravity) {
        vel.dy += gravity.gravity * dt.deltaTime;
    });
}