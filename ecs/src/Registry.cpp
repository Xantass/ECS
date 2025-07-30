#include "Registry.hpp"

Registry* g_registry = nullptr;
// Registry

Registry::Registry()
{
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        availableEntities.push(entity);
}

Entity Registry::createEntity()
{
    assert(livingEntityCount < MAX_ENTITIES && "Too many entities!");
    Entity id = availableEntities.front();
    availableEntities.pop();
    ++livingEntityCount;
    return id;
}

void Registry::destroyEntity(Entity entity)
{
    assert(entity < MAX_ENTITIES && "Entity out of range");
    entitySignatures[entity].reset();
    for (auto const &pair : componentArrays)
    {
        pair.second->entityDestroyed(entity);
    }
    availableEntities.push(entity);
    livingEntityCount--;
}

std::queue<Entity> &Registry::getAvailableEntities()
{
    return availableEntities;
}

AssetManager& Registry::getAssetManager()
{
    return assetManager;
}

EventBus& Registry::getEventBus()
{
    return eventBus;
}
