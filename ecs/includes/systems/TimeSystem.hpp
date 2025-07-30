#pragma once

#include "System.hpp"
#include "Time.hpp"
#include "DeltaTime.hpp"
#include "DeadEvent.hpp"
#include "Injectable.hpp"

class TimeSystem : public SystemBase<Time>, public Injectable<DeltaTime> {
public:
    void OnUpdate() override;

    INJECTABLE_MEMBERS(
        DeltaTime* deltaTime = nullptr;
    )
};

template<>
inline DeltaTime*& TimeSystem::getMember<DeltaTime>() { return deltaTime; }