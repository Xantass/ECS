#pragma once

#include "System.hpp"
#include "Cooldown.hpp"
#include "DeltaTime.hpp"
#include "Injectable.hpp"

class CooldownSystem : public SystemBase<Cooldown>, public Injectable<DeltaTime> {
public:
    void OnUpdate() override;

    INJECTABLE_MEMBERS(
        DeltaTime* deltaTime = nullptr;
    )
};

template<>
inline DeltaTime*& CooldownSystem::getMember<DeltaTime>() { return deltaTime; }