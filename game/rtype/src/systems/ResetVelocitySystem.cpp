#include "ResetVelocitySystem.hpp"
#include "Registry.hpp"

void ResetVelocitySystem::OnUpdate()
{
    registry->ForEach<Velocity, MainPlayer>([&](Entity /*entity*/, Velocity& vel, MainPlayer& /*player*/) {
        vel.dx = 0;
        vel.dy = 0;
    });
}