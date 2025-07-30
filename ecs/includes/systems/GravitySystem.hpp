#pragma once

#include "System.hpp"
#include "Velocity.hpp"
#include "Gravity.hpp"
#include "DeltaTime.hpp"

class GravitySystem : public SystemBase<Velocity, Gravity> {
public:
    void OnUpdate() override;
};