#include "GravitySystem.hpp"
#include "Registry.hpp"
#include "components/Time.hpp"

void GravitySystem::OnUpdate()
{
    // std::cout << "GravitySystem" << std::endl;
    registry->ForEach<Velocity, Gravity>([&](Entity /*entity*/, Velocity& vel, Gravity& gravity) {
        vel.dy += gravity.gravity * registry->getSingleton<DeltaTime>().deltaTime;
    });
}