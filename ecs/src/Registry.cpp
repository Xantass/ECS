#include "Registry.hpp"

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
    updateEntitySystems(entity, entitySignatures[entity]);
    for (auto const &pair : componentArrays)
    {
        pair.second->entityDestroyed(entity);
    }
    availableEntities.push(entity);
    livingEntityCount--;
}

void Registry::updateEntitySystems(Entity entity, Signature entitySignature)
{
    for (auto const &pair : systems)
    {
        auto const &type = pair.first;
        auto const &system = pair.second;
        auto const &systemSignature = systemSignatures[type];
        bool matches = (entitySignature & systemSignature) == systemSignature;
        if (matches)
        {
            system->entities.insert(entity);
        }
        else
        {
            system->entities.erase(entity);
        }
    }
}

std::unordered_map<std::string, std::shared_ptr<ISystem>> &Registry::getAllSystems(void)
{
    return systems;
}

std::shared_ptr<ISystem> Registry::getSystemByType(const std::string &name)
{
    auto it = systems.find(name);
    if (it != systems.end())
    {
        return it->second;
    }
    return nullptr;
}

std::queue<Entity> &Registry::getAvailableEntities()
{
    return availableEntities;
}

AssetManager& Registry::getAssetManager()
{
    return assetManager;
}

Signature Registry::getSignature(Entity entity)
{
    return entitySignatures[entity];
}

EventBus& Registry::getEventBus()
{
    return eventBus;
}

// Registry End

// ComponentArray

