#include "Engine.hpp"
#include "raylib.h"
#include <iostream>
#include "DeltaTime.hpp"
#include "Registry.hpp"
#include "System.hpp"

void autoRegister(Registry& registry, Engine& engine);

Engine::Engine(int width, int height, const char* title, std::string pathAssets)
    : screenWidth(width), screenHeight(height), windowTitle(title) {
    init(pathAssets);
}

Engine::~Engine() {
    shutdown();
}

void Engine::init(std::string pathAssets) {
    InitWindow(screenWidth, screenHeight, windowTitle);
    // ToggleFullscreen();
    SetTargetFPS(60);
    autoRegister(registry, *this);
    registry.getAssetManager().loadAllAssets(pathAssets);
}

void Engine::shutdown() {
    CloseWindow();
}

Registry& Engine::getRegistry() {
    return registry;
}

void Engine::run() {
    float currentTime = GetTime();
    while (!WindowShouldClose()) {
        float newTime = GetTime();
        float frameTime = newTime - currentTime;
        currentTime = newTime;

        if (frameTime > 0.25f)
            frameTime = 0.25f;

        timeAccumulator += frameTime;

        while (timeAccumulator >= fixedDeltaTime) {
            update(fixedDeltaTime);
            timeAccumulator -= fixedDeltaTime;
        }

        render();
    }
}

void Engine::update(float dt) {
    registry.setSingleton<DeltaTime>({dt});
    updateAllSystems();
}

void Engine::updateAllSystems() {
    for (auto& sys : systems) {
        // On suppose que tous les systèmes héritent de SystemBase<...>
        auto* base = static_cast<SystemBase<>*>(sys.get());
        if (base) base->OnUpdate();
    }
}

void Engine::renderFrame() {
    if (renderSystem) {
        renderSystem->OnUpdate();
    }
}

void Engine::render() {
    BeginDrawing();
    ClearBackground(BLACK);
    renderFrame();
    EndDrawing();
}