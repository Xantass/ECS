#pragma once

#include "Entity.hpp"
#include "Component.hpp"
#include "System.hpp"
#include "AssetManager.hpp"
#include "EventBus.hpp"
#include "InputEvent.hpp"
#include <functional>
#include <unordered_map>
#include <array>
#include <queue>
#include <memory>
#include <cassert>
#include <typeindex>
#include <set>
#include <iostream>
#include <tuple>
#include <vector>
#include <type_traits>
#include <any>

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void entityDestroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray
{
public:
    void insertData(Entity entity, T component)
    {
        assert(entityToIndex.find(entity) == entityToIndex.end() && "Component added twice");
        std::size_t index = size++;
        entityToIndex[entity] = index;
        indexToEntity[index] = entity;
        components[index] = component;
    }

    void removeData(Entity entity)
    {
        assert(entityToIndex.find(entity) != entityToIndex.end() && "Component does not exist");
        // std::cout << "Component: " << entityToIndex[entity] << std::endl;
        // std::cout << "--------------REMOVE DATA--------------" << std::endl;
        // std::cout << "index of entity: " << entityToIndex[entity] << std::endl;
        // std::cout << "size before remove: " << size << std::endl;
        // std::cout << "lastIndex: " << size - 1 << std::endl;
        // std::cout << "entity: " << entity << std::endl;
        std::size_t index = entityToIndex[entity];
        std::size_t lastIndex = size - 1;
        components[index] = components[lastIndex];

        Entity lastEntity = indexToEntity[lastIndex];
        entityToIndex[lastEntity] = index;
        indexToEntity[index] = lastEntity;

        // std::cout << "entityToIndex[entity]: " << entityToIndex[entity] << std::endl;
        // std::cout << "indexToEntity[lastIndex]: " << indexToEntity[lastIndex] << std::endl;
        entityToIndex.erase(entity);
        indexToEntity.erase(lastIndex);
        size--;
        // std::cout << "size after remove: " << size << std::endl;
        // std::cout << "--------------REMOVE DATA END----------" << std::endl;
    }

    T &getData(Entity entity)
    {
        assert(entityToIndex.find(entity) != entityToIndex.end() && "Component does not exist");
        return components[entityToIndex[entity]];
    }

    void entityDestroyed(Entity entity) override
    {
        if (entityToIndex.find(entity) != entityToIndex.end()) {
            // std::cout << "Component array: " << entity << std::endl;
            removeData(entity);
        }
    }

private:
    std::array<T, MAX_ENTITIES> components{};
    std::unordered_map<Entity, std::size_t> entityToIndex{};
    std::unordered_map<std::size_t, Entity> indexToEntity{};
    std::size_t size = 0;
};

class Registry
{
public:
    Registry();
    Entity createEntity();
    void destroyEntity(Entity entity);
    // Je retire les includes et membres liés à ISystem et signatures manuelles
    std::queue<Entity> &getAvailableEntities();
    AssetManager& getAssetManager();
    EventBus& getEventBus();

    template <typename T>
    void registerComponent()
    {
        const char *typeName = typeid(T).name();
        assert(componentTypes.find(typeName) == componentTypes.end() && "Component already registered");

        componentTypes[typeName] = nextComponentType;
        componentArrays[typeName] = std::make_shared<ComponentArray<T>>();
        ++nextComponentType;
    }

    template <typename T>
    void addComponent(Entity entity, T component)
    {
        getComponentArray<T>()->insertData(entity, component);
        entitySignatures[entity].set(getComponentType<T>(), true);
    }

    template <typename T>
    void removeComponent(Entity entity)
    {
        getComponentArray<T>()->removeData(entity);
        entitySignatures[entity].set(getComponentType<T>(), false);
    }

    template <typename T>
    T &getComponent(Entity entity)
    {
        // std::cout << "getComponent " << typeid(T).name() << " of entity: " << entity << std::endl;
        return getComponentArray<T>()->getData(entity);
    }

    template <typename T>
    bool hasComponent(Entity entity)
    {
        return entitySignatures[entity].test(getComponentType<T>());
    }

    template <typename T>
    ComponentType getComponentType()
    {
        const char *typeName = typeid(T).name();
        assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered");
        return componentTypes[typeName];
    }

    template <typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray()
    {
        const char *typeName = typeid(T).name();
        assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered");
        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
    }

    // Nouvelle API ForEach pour queries ergonomiques
    template<typename... Components, typename Func>
    void ForEach(Func func) {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            if (((hasComponent<Components>(entity)) && ...)) {
                func(entity, getComponent<Components>(entity)...);
            }
        }
    }

    // Gestion des singletons
    template<typename T>
    void setSingleton(const T& data) {
        singletons[typeid(T).hash_code()] = data;
    }
    template<typename T>
    T& getSingleton() {
        return std::any_cast<T&>(singletons.at(typeid(T).hash_code()));
    }

    // Gestion des ressources partagées (injection avancée)
    template<typename T>
    void setResource(std::shared_ptr<T> res) {
        resources[typeid(T)] = res;
    }
    template<typename T>
    T& getResource() {
        auto it = resources.find(typeid(T));
        if (it == resources.end())
            throw std::runtime_error("Resource not found");
        return *std::static_pointer_cast<T>(it->second);
    }

private:
    std::queue<Entity> availableEntities{};
    std::array<Signature, MAX_ENTITIES> entitySignatures{};
    std::unordered_map<std::string, ComponentType> componentTypes{};
    std::unordered_map<std::string, std::shared_ptr<IComponentArray>> componentArrays{};
    std::unordered_map<std::string, Signature> systemSignatures{};
    ComponentType nextComponentType = 0;
    std::uint32_t livingEntityCount = 0;
    AssetManager assetManager;
    EventBus eventBus;
    std::unordered_map<size_t, std::any> singletons;
    std::unordered_map<std::type_index, std::shared_ptr<void>> resources;
};