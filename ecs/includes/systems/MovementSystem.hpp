#pragma once

#include "System.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "DeltaTime.hpp"

class MovementSystem : public SystemBase<Position, Velocity> {
public:
    void OnUpdate() override;
};
