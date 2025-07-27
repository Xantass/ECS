#pragma once

#include "Registry.hpp"
#include "DeadEvent.hpp"
#include "Health.hpp"

class LifeSystem : public ISystem {
    public:
        void update(Registry& registry, float dt) override;
};