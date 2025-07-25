#pragma once

#include "Entity.hpp"
#include <set>

class Registry;

class ISystem {
public:
    virtual ~ISystem() = default;
    virtual void update(Registry& registry, float dt) = 0;
    std::set<Entity> entities;
};