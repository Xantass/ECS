#include "InputSystem.hpp"
#include "Registry.hpp"

struct KeyMap { InputType type; int key; };
        std::vector<KeyMap> keys = {
            {InputType::KeyRight, KEY_RIGHT},
            {InputType::KeyLeft,  KEY_LEFT},
            {InputType::KeyDown,  KEY_DOWN},
            {InputType::KeyUp,    KEY_UP},
            {InputType::KeySpace, KEY_SPACE},
            {InputType::KeyTab, KEY_TAB}
        };

void InputSystem::OnUpdate()
{
    auto& eventBus = registry->getEventBus();
    auto& dt = registry->getSingleton<DeltaTime>();
    const float inputDelay = 0.2f;

    registry->ForEach<CooldownInput>([&](Entity entity, CooldownInput& cooldown) {

        bool anyPressed = false;
        for (auto& k : keys) {
            cooldown.timers[k.type] += dt.deltaTime;
            if (IsKeyDown(k.key) && k.key == KEY_TAB && cooldown.timers[k.type] >= inputDelay) {
                eventBus.emit(InputEvent{k.type, entity});
                cooldown.timers[k.type] = 0.0f;
                anyPressed = true;
            } else if (IsKeyDown(k.key) && k.key != KEY_TAB) {
                eventBus.emit(InputEvent{k.type, entity});
                cooldown.timers[k.type] = 0.0f;
                anyPressed = true;
            }
        }
        if (!anyPressed) {
            eventBus.emit(InputEvent{InputType::KeyNone, entity});
        }
    });
}