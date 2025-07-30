#pragma once

#include "System.hpp"
#include "Velocity.hpp"
#include "MainPlayer.hpp"

class ResetVelocitySystem : public SystemBase<Velocity, MainPlayer> {
public:
    void OnUpdate() override;
};