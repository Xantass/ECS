#pragma once

#include "System.hpp"
#include "Sprite.hpp"
#include "Position.hpp"
#include "Debug.hpp"
#include "raylib.h"

class DebugDrawSystem : public SystemBase<Position, Sprite> {
public:
    void OnUpdate() override;
};