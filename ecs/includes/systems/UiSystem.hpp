#pragma once

#include "Registry.hpp"
#include "System.hpp"
#include "raylib.h"

class UiSystem : public ISystem
{
    public:
        void update(Registry& registry, float dt) override;
};