#pragma once

#include "System.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Injectable.hpp"
#include "DeltaTime.hpp"

class MovementSystem : public SystemBase<Position, Velocity>, public Injectable<DeltaTime> {
public:
    void OnUpdate() override;

    INJECTABLE_MEMBERS(
        DeltaTime* deltaTime = nullptr;
        template<> DeltaTime*& getMember<DeltaTime>() { return deltaTime; }
    )
};
