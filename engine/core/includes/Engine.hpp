#pragma once

#include "raylib.h"
#include "Registry.hpp"
#include "Component.hpp"
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <iostream>

class Engine {
public:
    Engine(int width, int height, const char* title);
    ~Engine();

    void run();

    Registry& getRegistry();

    template<typename T, typename... Components>
    T& registerSystem() {
        auto system = registry.registerSystem<T>();
        Signature sig;
        (sig.set(registry.getComponentType<Components>()), ...);
        registry.setSystemSignature<T>(sig);
        return *system;
    }

private:
    int screenWidth;
    int screenHeight;
    const char* windowTitle;

    float fixedDeltaTime = 1.0f / 60.0f;
    float timeAccumulator = 0.0f;

    Registry registry;

    void init();
    void shutdown();
    void update(float dt);
    void render();
};

