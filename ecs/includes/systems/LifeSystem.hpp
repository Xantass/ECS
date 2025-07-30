#pragma once

#include "Health.hpp"
#include "DeadEvent.hpp"
#include "System.hpp"
#include "EventBus.hpp"

class LifeSystem : public SystemBase<Health> {
public:
    void OnUpdate() override;
};