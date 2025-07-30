#pragma once

#include "System.hpp"
#include "Cooldown.hpp"
#include "DeltaTime.hpp"

class CooldownSystem : public SystemBase<Cooldown> {
public:
    void OnUpdate() override;
};