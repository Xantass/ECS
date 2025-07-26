#include "Engine.hpp"
#include "InputAction.hpp"
#include "Registry.hpp"
#include "RenderSystem.hpp"
#include "MovementSystem.hpp"
#include "InputSystem.hpp"
#include "CollisionSystem.hpp"
#include "Cooldown.hpp"
#include "Gravity.hpp"
#include "AssetManager.hpp"

#include "raylib.h"

void setupReaction(Registry& registry);

int main() {
    Engine engine(1920, 1080, "R-Type Engine");

    Registry& registry = engine.getRegistry();    

    // Créer les entités
    Entity player = registry.createEntity();
    registry.addComponent(player, Position{100, 100});
    registry.addComponent(player, Velocity{0, 0});
    registry.addComponent(player, Sprite{registry.getAssetManager().getTexture("player"), 1.0f});
    registry.addComponent(player, MainPlayer{});
    registry.addComponent(player, Speed{300});
    registry.addComponent(player, Collider{static_cast<float>(registry.getAssetManager().getTexture("player").width), static_cast<float>(registry.getAssetManager().getTexture("player").height)});
    registry.addComponent(player, Cooldown{0.0f, 0.2f});

    setupActions(registry, player);
    setupReaction(registry);

    Entity enemy = registry.createEntity();
    registry.addComponent(enemy, Position{900, 100});
    registry.addComponent(enemy, Velocity{0, 0});
    registry.addComponent(enemy, Sprite{registry.getAssetManager().getTexture("enemy"), 1.0f});
    registry.addComponent(enemy, Enemy{});
    registry.addComponent(enemy, Collider{static_cast<float>(registry.getAssetManager().getTexture("enemy").width), static_cast<float>(registry.getAssetManager().getTexture("enemy").height)});
    registry.addComponent(enemy, Gravity{100});

    engine.run();

    AssetManager::unloadAll();
    return 0;
}