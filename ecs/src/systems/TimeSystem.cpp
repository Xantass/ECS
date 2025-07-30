#include "TimeSystem.hpp"
#include "Registry.hpp"
#include "components/Time.hpp"

void TimeSystem::OnUpdate()
{
    registry->ForEach<Time>([&](Entity entity, Time& time) {
        time.time -= registry->getSingleton<DeltaTime>().deltaTime;
        if (time.time <= 0) {
            registry->getEventBus().emit(DeadEvent{entity});
        }
    });
}