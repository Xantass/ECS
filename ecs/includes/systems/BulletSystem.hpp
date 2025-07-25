#pragma once

#include "System.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Bullet.hpp"
#include "Registry.hpp"
#include "raylib.h"

class BulletSystem : public ISystem {
public:
    void update(Registry& registry, float dt) override;
};