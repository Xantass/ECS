#include "CollisionSystem.hpp"
#include "Registry.hpp"

#define SCALE 4.0f


void CollisionSystem::OnUpdate()
{
    // std::cout << "CollisionSystem" << std::endl;
    const int cellSize = 64;
    using CellKey = std::pair<int, int>;
    std::unordered_map<CellKey, std::vector<Entity>, pair_hash> spatialGrid;

    auto hash = [&](float x, float y) -> CellKey {
        return {static_cast<int>(x) / cellSize, static_cast<int>(y) / cellSize};
    };

    registry->ForEach<Position, Collider>([&](Entity e, Position& pos, Collider&) {
        CellKey key = hash(pos.x, pos.y);
        spatialGrid[key].push_back(e);
    });

    for (const auto &[key, cellEntities] : spatialGrid) {
        for (Entity a : cellEntities) {
            if (!registry->hasComponent<Bullet>(a))
                continue;
            auto &aPos = registry->getComponent<Position>(a);
            auto &aCol = registry->getComponent<Collider>(a);
            for (Entity b : cellEntities) {
                if (!registry->hasComponent<Enemy>(b) || a == b)
                    continue;
                auto &bPos = registry->getComponent<Position>(b);
                auto &bCol = registry->getComponent<Collider>(b);
                if (checkAABBCollision(aPos, aCol, bPos, bCol)) {
                    registry->getEventBus().emit(CollisionEvent{a, b});
                    break;
                }
            }
        }
    }
}

bool CollisionSystem::checkAABBCollision(const Position &aPos, const Collider &aCol, const Position &bPos, const Collider &bCol)
{
    return (
        aPos.x < bPos.x + bCol.width * SCALE &&
        aPos.x + aCol.width * SCALE > bPos.x &&
        aPos.y < bPos.y + bCol.height * SCALE &&
        aPos.y + aCol.height * SCALE > bPos.y
    );
}