#include "InputSystem.hpp"

#define MAX_GAMEPADS 4

void InputSystem::update(Registry &registry, float /*dt*/)
{
    auto entitiesCopy = entities;
    for (auto entity : entitiesCopy)
    {
        // std::cout << "InputSystem: " << entity << std::endl;
        // auto &cooldown = registry.getComponent<Cooldown>(entity);
        auto &vel = registry.getComponent<Velocity>(entity);
        // auto &gamepad = registry.getComponent<Gamepad>(entity);

        vel.dx = 0;
        vel.dy = 0;
        
        // if (gamepad.id != -1) {
        //     std::cout << "Gamepad: " << gamepad.id << std::endl;
        //     if (IsGamepadButtonPressed(gamepad.id, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
        //         registry.getEventBus().emit(InputEvent{InputType::KeyRight, entity});
        //     if (IsGamepadButtonPressed(gamepad.id, GAMEPAD_BUTTON_RIGHT_FACE_UP))
        //         registry.getEventBus().emit(InputEvent{InputType::KeyLeft, entity});
        //     if (IsGamepadButtonPressed(gamepad.id, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
        //         registry.getEventBus().emit(InputEvent{InputType::KeyDown, entity});
        //     if (IsGamepadButtonPressed(gamepad.id, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
        //         registry.getEventBus().emit(InputEvent{InputType::KeyUp, entity});
        //     if (IsGamepadButtonPressed(gamepad.id, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
        //         registry.getEventBus().emit(InputEvent{InputType::KeySpace, entity});
        // }

        if (IsKeyDown(KEY_RIGHT))
            registry.getEventBus().emit(InputEvent{InputType::KeyRight, entity});
        if (IsKeyDown(KEY_LEFT))
            registry.getEventBus().emit(InputEvent{InputType::KeyLeft, entity});
        if (IsKeyDown(KEY_DOWN))
            registry.getEventBus().emit(InputEvent{InputType::KeyDown, entity});
        if (IsKeyDown(KEY_UP))
            registry.getEventBus().emit(InputEvent{InputType::KeyUp, entity});
        if (IsKeyDown(KEY_SPACE))
            registry.getEventBus().emit(InputEvent{InputType::KeySpace, entity});
    }
}