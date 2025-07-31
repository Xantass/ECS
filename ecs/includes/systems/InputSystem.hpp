#pragma once

#include "System.hpp"
#include "Velocity.hpp"
#include "MainPlayer.hpp"
#include "CooldownInput.hpp"
#include "EventBus.hpp"
#include "DeltaTime.hpp"
#include "raylib.h"

class InputSystem : public SystemBase<Velocity, MainPlayer, CooldownInput> {
public:
    void OnUpdate() override;
};
