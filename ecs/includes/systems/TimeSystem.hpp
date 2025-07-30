#pragma once

#include "System.hpp"
#include "Time.hpp"
#include "DeltaTime.hpp"
#include "DeadEvent.hpp"

class TimeSystem : public SystemBase<Time> {
public:
    void OnUpdate() override;
};