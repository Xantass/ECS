#pragma once

#include "System.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Position.hpp"
#include "Registry.hpp"
#include "raylib.h"
#include "CollisionEvent.hpp"

class CollisionSystem : public ISystem {
public:
    void update(Registry& registry, float dt) override;

private:
    struct pair_hash {
        template <class T1, class T2>
        std::size_t operator()(const std::pair<T1, T2>& p) const {
            auto h1 = std::hash<T1>{}(p.first);
            auto h2 = std::hash<T2>{}(p.second);
            return h1 ^ (h2 << 1);
        }
    };

    bool checkAABBCollision(const Position& aPos, const Collider& aCol, const Position& bPos, const Collider& bCol);
};

