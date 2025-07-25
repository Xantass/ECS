#pragma once

#include "System.hpp"
#include "Component.hpp"
#include "Sprite.hpp"
#include "Position.hpp"
#include "Registry.hpp"
#include "raylib.h"

#include <iostream>

class RenderSystem : public ISystem {
public:
    void update(Registry& registry, float dt) override;
};
