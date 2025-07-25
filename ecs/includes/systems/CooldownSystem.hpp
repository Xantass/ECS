#pragma once

#include "System.hpp"
#include "Cooldown.hpp"
#include "Registry.hpp"

class CooldownSystem : public ISystem {
public:
    void update(Registry& registry, float dt) override;
};