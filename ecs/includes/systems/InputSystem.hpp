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
#include "Gamepad.hpp"
#include "raylib.h"
#include "EventBus.hpp"

class InputSystem : public SystemBase<Velocity, MainPlayer> {
public:
    void OnUpdate() override;
};
