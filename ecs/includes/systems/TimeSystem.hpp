#pragma once

#include "System.hpp"
#include "Registry.hpp"
#include "Time.hpp"

class TimeSystem : public ISystem
{
    public:
        void update(Registry& registry, float dt) override;
};