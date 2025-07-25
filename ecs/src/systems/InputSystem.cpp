#include "InputSystem.hpp"

void InputSystem::update(Registry &registry, float /*dt*/)
{
    auto entitiesCopy = entities;
    for (auto entity : entitiesCopy)
    {
        // std::cout << "InputSystem: " << entity << std::endl;
        auto &cooldown = registry.getComponent<Cooldown>(entity);
        auto &vel = registry.getComponent<Velocity>(entity);

        vel.dx = 0;
        vel.dy = 0;

        if (IsKeyDown(KEY_RIGHT))
            registry.getEventBus().emit(InputEvent{InputType::KeyRight, entity});
        if (IsKeyDown(KEY_LEFT))
            registry.getEventBus().emit(InputEvent{InputType::KeyLeft, entity});
        if (IsKeyDown(KEY_DOWN))
            registry.getEventBus().emit(InputEvent{InputType::KeyDown, entity});
        if (IsKeyDown(KEY_UP))
            registry.getEventBus().emit(InputEvent{InputType::KeyUp, entity});
        if (IsKeyDown(KEY_SPACE) && cooldown.timer >= cooldown.interval)
            registry.getEventBus().emit(InputEvent{InputType::KeySpace, entity});
    }
}