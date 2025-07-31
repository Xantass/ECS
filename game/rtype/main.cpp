#include "Engine.hpp"
#include "InputAction.hpp"
#include "Registry.hpp"
#include "RenderSystem.hpp"
#include "MovementSystem.hpp"
#include "InputSystem.hpp"
#include "CollisionSystem.hpp"
#include "Cooldown.hpp"
#include "Gravity.hpp"
#include "Health.hpp"
#include "Gamepad.hpp"
#include "Speed.hpp"
#include "CooldownInput.hpp"
#include "AssetManager.hpp"

#include "raylib.h"

#define SCALE 4.0f

void setupReaction(Registry& registry);

int main() {
    Engine engine(1920, 1080, "R-Type Engine", "assets/rtype/");

    Registry& registry = engine.getRegistry();    

    // Créer les entités
    Entity player = registry.createEntity();
    registry.addComponent(player, MainPlayer{});
    registry.addComponent(player, Position{100, 100});
    registry.addComponent(player, Velocity{0, 0});
    registry.addComponent(player, Sprite{registry.getAssetManager().getTexture("Ships"), registry.getAssetManager().getFrame("silver_ship")});
    registry.addComponent(player, Speed{300});
    registry.addComponent(player, Collider{static_cast<float>(registry.getAssetManager().getFrame("silver_ship").width) * SCALE, static_cast<float>(registry.getAssetManager().getFrame("silver_ship").height) * SCALE});
    registry.addComponent(player, Cooldown{0.0f, 0.2f});
    registry.addComponent(player, CooldownInput{});
    registry.addComponent(player, Health{100, 100});
    if (IsGamepadAvailable(0))
        registry.addComponent(player, Gamepad{0});
    else
        registry.addComponent(player, Gamepad{-1});

    setupActions(registry, player);
    setupReaction(registry);

    Entity enemy = registry.createEntity();
    registry.addComponent(enemy, Position{900, 100});
    registry.addComponent(enemy, Velocity{0, 0});
    registry.addComponent(enemy, Sprite{registry.getAssetManager().getTexture("Ships"), registry.getAssetManager().getFrame("enemy_purple")});
    registry.addComponent(enemy, Enemy{});
    registry.addComponent(enemy, Collider{static_cast<float>(registry.getAssetManager().getFrame("enemy_purple").width) * SCALE, static_cast<float>(registry.getAssetManager().getFrame("enemy_purple").height) * SCALE});
    // registry.addComponent(enemy, Gravity{100});
    registry.addComponent(enemy, Health{100, 100});

    engine.run();

    AssetManager::unloadAll();
    return 0;
}