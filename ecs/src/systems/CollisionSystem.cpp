#include "CollisionSystem.hpp"
#include "Registry.hpp"

#define SCALE 4.0f

void CollisionSystem::OnUpdate()
{
    const int cellSize = 64;
    using CellKey = std::pair<int, int>;
    std::unordered_map<CellKey, std::vector<Entity>, pair_hash> spatialGrid;

    // auto hash = [&](float x, float y) -> CellKey {
    //     return {static_cast<int>(x) / cellSize, static_cast<int>(y) / cellSize};
    // };

    registry->ForEach<Position, Collider>([&](Entity e, Position &pos, Collider &col)
                                          {
        int minX = static_cast<int>(pos.x) / cellSize;
        int minY = static_cast<int>(pos.y) / cellSize;
        int maxX = static_cast<int>(pos.x + col.width * SCALE) / cellSize;
        int maxY = static_cast<int>(pos.y + col.height * SCALE) / cellSize;

        for (int x = minX; x <= maxX; ++x) {
            for (int y = minY; y <= maxY; ++y) {
                CellKey key = {x, y};
                spatialGrid[key].push_back(e);
            }
        } });

    // std::cout << "=== Grille spatiale ===" << std::endl;
    // for (const auto &[key, entities] : spatialGrid)
    // {
    //     std::cout << "Cellule (" << key.first << ", " << key.second << ") : ";
    //     for (const auto &entity : entities)
    //     {
    //         std::cout << entity << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << "======================" << std::endl;


    std::set<std::pair<Entity, Entity>> alreadyChecked;
    for (const auto &[key, cellEntities] : spatialGrid)
    {
        for (Entity a : cellEntities)
        {
            // std::cout << "First loop Entity " << a << std::endl;
            if (!registry->isAlive(a)) {
                // std::cout << "Entity " << a << " is not alive" << std::endl;
                continue;
            }
            auto aPos = registry->getComponent<Position>(a);
            auto aCol = registry->getComponent<Collider>(a);
            aPos.x -= aCol.width;
            for (Entity b : cellEntities)
            {
                // std::cout << "Second loop Entity " << b << std::endl;
                if ((!registry->isAlive(b) || !registry->isAlive(a)) || a == b) {
                    // std::cout << "Entity " << a << " is not alive" << std::endl;
                    // std::cout << "Entity " << b << " is not alive" << std::endl;
                    continue;
                }
                auto bPos = registry->getComponent<Position>(b);
                auto bCol = registry->getComponent<Collider>(b);
                bPos.x -= bCol.width;

                if (checkAABBCollision(aPos, aCol, bPos, bCol) && (alreadyChecked.find({a, b}) == alreadyChecked.end() || alreadyChecked.find({b, a}) == alreadyChecked.end()))
                {
                    alreadyChecked.insert({a, b});
                    alreadyChecked.insert({b, a});
                    std::cout << "---------------Collision detected--------------------" << std::endl;
                    std::cout << "Cellule (" << key.first << ", " << key.second << ") : " << std::endl;
                    std::cout << "CollisionSystem entity: " << a << std::endl;
                    std::cout << "Position: " << aPos.x << ", " << aPos.y << std::endl;
                    std::cout << "Collider: " << aCol.width << ", " << aCol.height << std::endl;
                    std::cout << "CollisionSystem entity: " << b << std::endl;
                    std::cout << "Position: " << bPos.x << ", " << bPos.y << std::endl;
                    std::cout << "Collider: " << bCol.width << ", " << bCol.height << std::endl;
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
        aPos.x < bPos.x + bCol.width &&
        aPos.x + aCol.width > bPos.x &&
        aPos.y < bPos.y + bCol.height &&
        aPos.y + aCol.height > bPos.y);
}