#pragma once

#include "System.hpp"
#include "Sprite.hpp"
#include "Position.hpp"
#include "raylib.h"

#define SCALE 4.0f

class RenderSystem : public SystemBase<Position, Sprite> {
public:
    void OnUpdate() override;
};
