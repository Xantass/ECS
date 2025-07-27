#include "InputAction.hpp"
#include "Registry.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Bullet.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Cooldown.hpp"
#include "Speed.hpp"

std::map<InputType, InputAction> actions;

void setupActions(Registry &registry, Entity playerId)
{
    std::cout << "setupActions" << std::endl;
    actions[InputType::KeyLeft] = [&registry, playerId]()
    {
        auto &vel = registry.getComponent<Velocity>(playerId);
        auto &speed = registry.getComponent<Speed>(playerId);

        vel.dx -= speed.speed;
    };
    actions[InputType::KeyRight] = [&registry, playerId]()
    {
        auto &vel = registry.getComponent<Velocity>(playerId);
        auto &speed = registry.getComponent<Speed>(playerId);

        vel.dx += speed.speed;
    };
    actions[InputType::KeyUp] = [&registry, playerId]()
    {
        auto &vel = registry.getComponent<Velocity>(playerId);
        auto &speed = registry.getComponent<Speed>(playerId);

        vel.dy -= speed.speed;
    };
    actions[InputType::KeyDown] = [&registry, playerId]()
    {
        auto &vel = registry.getComponent<Velocity>(playerId);
        auto &speed = registry.getComponent<Speed>(playerId);

        vel.dy += speed.speed;
    };
    actions[InputType::KeySpace] = [&registry, playerId]()
    {   
        auto &pos = registry.getComponent<Position>(playerId);
        auto &cooldown = registry.getComponent<Cooldown>(playerId);

        if (cooldown.timer < cooldown.interval) return;
        auto bullet = registry.createEntity();
        cooldown.timer = 0.0f;
        registry.addComponent(bullet, Position{pos.x + 100, pos.y + 20});
        registry.addComponent(bullet, Velocity{500, 0});
        registry.addComponent(bullet, Bullet{2.0f, 50});
        registry.addComponent(bullet, Sprite{registry.getAssetManager().getTexture("bullet"), 1.0f});
        registry.addComponent(bullet, Collider{static_cast<float>(registry.getAssetManager().getTexture("bullet").width), static_cast<float>(registry.getAssetManager().getTexture("bullet").height)});
    };
    registry.getEventBus().subscribe<InputEvent>([&](const InputEvent& event) {
        auto it = actions.find(event.type);
        if (it != actions.end())
            it->second();
    });
}