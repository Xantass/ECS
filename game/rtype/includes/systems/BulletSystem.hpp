#pragma once

#include "System.hpp"
#include "Position.hpp"
#include "Bullet.hpp"
#include "raylib.h"
#include "EventBus.hpp"
#include "Injectable.hpp"

class BulletSystem : public SystemBase<Position, Bullet>, public Injectable<EventBus> {
public:
    void OnUpdate() override;

    INJECTABLE_MEMBERS(
        EventBus* eventBus = nullptr;
    )
};

template<>
inline EventBus*& BulletSystem::getMember<EventBus>() { return eventBus; }