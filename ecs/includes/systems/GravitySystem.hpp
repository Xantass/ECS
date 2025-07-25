#pragma once

#include "System.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Gravity.hpp"
#include "Registry.hpp"
#include "raylib.h"

class GravitySystem : public ISystem {
public:
    void update(Registry& registry, float dt) override;
};