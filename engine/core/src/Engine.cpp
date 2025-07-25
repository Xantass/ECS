#include "Engine.hpp"
#include "raylib.h"
#include <iostream>

void autoRegister(Registry& registry, Engine& engine);

Engine::Engine(int width, int height, const char* title)
    : screenWidth(width), screenHeight(height), windowTitle(title) {
    init();
}

Engine::~Engine() {
    shutdown();
}

void Engine::init() {
    InitWindow(screenWidth, screenHeight, windowTitle);
    ToggleFullscreen();
    SetTargetFPS(60);
    autoRegister(registry, *this);
    registry.getAssetManager().loadAllAssets("assets/");
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
    for (auto& [name, sys] : registry.getAllSystems()) {
        // std::cout << "System: " << name << std::endl;
        sys->update(registry, dt);
    }
}

void Engine::render() {
    BeginDrawing();
    ClearBackground(BLACK);

    auto renderSys = registry.getSystemByType("RenderSystem");
    if (renderSys)
        renderSys->update(registry, 0.0f);

    EndDrawing();
}