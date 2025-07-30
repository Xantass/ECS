#pragma once

#include "raylib.h"
#include "Registry.hpp"
#include "Component.hpp"
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <iostream>
#include <vector>
#include "Injectable.hpp"
#include "RenderSystem.hpp"

class Engine {
public:
    Engine(int width, int height, const char* title, std::string pathAssets);
    ~Engine();

    void run();

    Registry& getRegistry();

    template<typename T>
    T& registerSystem() {
        auto system = std::make_shared<T>();
        system->setRegistry(&registry);
        injectIfNeeded(*system);
        systems.push_back(system);
        return *system;
    }
    void updateAllSystems();
    void setRenderSystem(RenderSystem* sys) { renderSystem = sys; }
    void renderFrame();

private:
    int screenWidth;
    int screenHeight;
    const char* windowTitle;

    float fixedDeltaTime = 1.0f / 60.0f;
    float timeAccumulator = 0.0f;

    Registry registry;
    std::vector<std::shared_ptr<void>> systems;
    RenderSystem* renderSystem = nullptr;

    void init(std::string pathAssets);
    void shutdown();
    void update(float dt);
    void render();

    template<typename T>
    void injectIfNeeded(T&) {}
    template<typename T, typename... Resources>
    void injectIfNeeded(Injectable<Resources...>& sys) {
        sys.inject(registry.getResource<Resources>()...);
    }
};

