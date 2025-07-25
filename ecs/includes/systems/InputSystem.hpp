#pragma once

#include "System.hpp"
#include "Velocity.hpp"
#include "MainPlayer.hpp"
#include "Speed.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"
#include "Cooldown.hpp"
#include "Position.hpp"
#include "Sprite.hpp"
#include "Registry.hpp"
#include "raylib.h"
#include <iostream>

class InputSystem : public ISystem {
public:
    void update(Registry& registry, float dt) override;
};
