#include "InputSystem.hpp"
#include "Registry.hpp"

void InputSystem::OnUpdate()
{
    registry->ForEach<Velocity, MainPlayer>([&](Entity entity, Velocity& vel, MainPlayer& /*player*/) {
        bool isPressed = false;
        vel.dx = 0;
        vel.dy = 0;
        if (IsKeyDown(KEY_RIGHT)) {
            eventBus->emit(InputEvent{InputType::KeyRight, entity});
            isPressed = true;
        }
        if (IsKeyDown(KEY_LEFT)) {
            eventBus->emit(InputEvent{InputType::KeyLeft, entity});
            isPressed = true;
        }
        if (IsKeyDown(KEY_DOWN)) {
            eventBus->emit(InputEvent{InputType::KeyDown, entity});
            isPressed = true;
        }
        if (IsKeyDown(KEY_UP)) {
            eventBus->emit(InputEvent{InputType::KeyUp, entity});
            isPressed = true;
        }
        if (IsKeyDown(KEY_SPACE)) {
            eventBus->emit(InputEvent{InputType::KeySpace, entity});
            isPressed = true;
        }
        if (!isPressed)
            eventBus->emit(InputEvent{InputType::KeyNone, entity});
    });
}