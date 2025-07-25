#include "CollisionSystem.hpp"

void CollisionSystem::update(Registry &registry, float /*dt*/)
{
    const int cellSize = 64;
    using CellKey = std::pair<int, int>;
    std::unordered_map<CellKey, std::vector<Entity>, pair_hash> spatialGrid;

    auto hash = [&](float x, float y) -> CellKey
    {
        return {static_cast<int>(x) / cellSize, static_cast<int>(y) / cellSize};
    };

    for (Entity e : entities)
    {
        if (!registry.hasComponent<Position>(e) || !registry.hasComponent<Collider>(e))
            continue;
        auto &pos = registry.getComponent<Position>(e);
        CellKey key = hash(pos.x, pos.y);
        spatialGrid[key].push_back(e);
    }

    for (const auto &[key, cellEntities] : spatialGrid)
    {
        for (Entity a : cellEntities)
        {
            if (!registry.hasComponent<Bullet>(a))
                continue;
            auto &aPos = registry.getComponent<Position>(a);
            auto &aCol = registry.getComponent<Collider>(a);

            for (Entity b : cellEntities)
            {
                if (!registry.hasComponent<Enemy>(b) || a == b)
                    continue;
                auto &bPos = registry.getComponent<Position>(b);
                auto &bCol = registry.getComponent<Collider>(b);

                if (checkAABBCollision(aPos, aCol, bPos, bCol))
                {
                    registry.destroyEntity(a);
                    registry.destroyEntity(b);
                    break;
                }
            }
        }
    }
}

bool CollisionSystem::checkAABBCollision(const Position &aPos, const Collider &aCol, const Position &bPos, const Collider &bCol)
{
    return (
        aPos.x < bPos.x + bCol.width &&
        aPos.x + aCol.width > bPos.x &&
        aPos.y < bPos.y + bCol.height &&
        aPos.y + aCol.height > bPos.y
    );
}