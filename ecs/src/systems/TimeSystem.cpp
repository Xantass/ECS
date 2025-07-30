#include "TimeSystem.hpp"
#include "Registry.hpp"
#include "components/Time.hpp"

void TimeSystem::OnUpdate()
{
    auto& dt = registry->getSingleton<DeltaTime>();
    registry->ForEach<Time>([&](Entity entity, Time& time) {
        time.time -= dt.deltaTime;
        if (time.time <= 0) {
            registry->getEventBus().emit(DeadEvent{entity});
        }
    });
}