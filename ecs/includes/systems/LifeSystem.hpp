#pragma once

#include "Health.hpp"
#include "DeadEvent.hpp"
#include "System.hpp"
#include "EventBus.hpp"
#include "Injectable.hpp"

class LifeSystem : public SystemBase<Health>, public Injectable<EventBus> {
public:
    void OnUpdate() override;

    INJECTABLE_MEMBERS(
        EventBus* eventBus = nullptr;
        template<> EventBus*& getMember<EventBus>() { return eventBus; }
    )
};