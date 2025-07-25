#pragma once

#include "System.hpp"
#include "Component.hpp"
#include "Velocity.hpp"
#include "Position.hpp"
#include "Registry.hpp"

#include "Registry.hpp"

class MovementSystem : public ISystem {
public:
    void update(Registry& registry, float dt) override;
};
