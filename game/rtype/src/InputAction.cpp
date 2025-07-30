#include "InputAction.hpp"
#include "Registry.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Bullet.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Cooldown.hpp"
#include "Speed.hpp"
#include "Time.hpp"

std::map<InputType, InputAction> actions;

void setupActions(Registry &registry, Entity playerId)
{
    // std::cout << "setupActions" << std::endl;
    actions[InputType::KeyLeft] = [&registry, playerId]()
    {
        auto &vel = registry.getComponent<Velocity>(playerId);
        auto &speed = registry.getComponent<Speed>(playerId);
        auto &sprite = registry.getComponent<Sprite>(playerId);

        sprite.frame = registry.getAssetManager().getFrame("silver_ship");
        vel.dx -= speed.speed;
    };
    actions[InputType::KeyRight] = [&registry, playerId]()
    {
        auto &vel = registry.getComponent<Velocity>(playerId);
        auto &speed = registry.getComponent<Speed>(playerId);
        auto &sprite = registry.getComponent<Sprite>(playerId);

        sprite.frame = registry.getAssetManager().getFrame("silver_ship");
        vel.dx += speed.speed;
    };
    actions[InputType::KeyUp] = [&registry, playerId]()
    {
        auto &vel = registry.getComponent<Velocity>(playerId);
        auto &speed = registry.getComponent<Speed>(playerId);
        auto &sprite = registry.getComponent<Sprite>(playerId);

        sprite.frame = registry.getAssetManager().getFrame("silver_ship_up");
        vel.dy -= speed.speed;
    };
    actions[InputType::KeyDown] = [&registry, playerId]()
    {
        auto &vel = registry.getComponent<Velocity>(playerId);
        auto &speed = registry.getComponent<Speed>(playerId);
        auto &sprite = registry.getComponent<Sprite>(playerId);

        sprite.frame = registry.getAssetManager().getFrame("silver_ship_down");
        vel.dy += speed.speed;
    };
    actions[InputType::KeySpace] = [&registry, playerId]()
    {   
        std::cout << "KeySpace" << std::endl;
        auto &pos = registry.getComponent<Position>(playerId);
        auto &cooldown = registry.getComponent<Cooldown>(playerId);

        if (cooldown.timer < cooldown.interval) return;
        auto bullet = registry.createEntity();
        cooldown.timer = 0.0f;
        registry.addComponent(bullet, Time{2.0f});
        registry.addComponent(bullet, Position{pos.x + static_cast<float>(registry.getAssetManager().getFrame("rocket").width) / 2, pos.y + static_cast<float>(registry.getAssetManager().getFrame("rocket").height) / 2});
        registry.addComponent(bullet, Velocity{500, 0});
        registry.addComponent(bullet, Bullet{50});
        registry.addComponent(bullet, Sprite{registry.getAssetManager().getTexture("Projectiles"), registry.getAssetManager().getFrame("rocket")});
        registry.addComponent(bullet, Collider{static_cast<float>(registry.getAssetManager().getFrame("rocket").width), static_cast<float>(registry.getAssetManager().getFrame("rocket").height)});
    };
    actions[InputType::KeyNone] = [&registry, playerId]()
    {
        auto &sprite = registry.getComponent<Sprite>(playerId);
        sprite.frame = registry.getAssetManager().getFrame("silver_ship");
    };
    registry.getEventBus().subscribe<InputEvent>([&](const InputEvent& event) {
        auto it = actions.find(event.type);
        if (it != actions.end())
            it->second();
    });
}