#pragma once

#include "System.hpp"
#include "Velocity.hpp"
#include "Gravity.hpp"
#include "Injectable.hpp"
#include "DeltaTime.hpp"

class GravitySystem : public SystemBase<Velocity, Gravity>, public Injectable<DeltaTime> {
public:
    void OnUpdate() override;

    INJECTABLE_MEMBERS(
        DeltaTime* deltaTime = nullptr;
    )
};

template<>
inline DeltaTime*& GravitySystem::getMember<DeltaTime>() { return deltaTime; }