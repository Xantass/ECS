#include "Registry.hpp"
#include "Engine.hpp"
#include "Collider.hpp"
#include "Cooldown.hpp"
#include "Enemy.hpp"
#include "Gravity.hpp"
#include "Health.hpp"
#include "MainPlayer.hpp"
#include "Position.hpp"
#include "Speed.hpp"
#include "Sprite.hpp"
#include "Velocity.hpp"
#include "InputSystem.hpp"
#include "MovementSystem.hpp"
#include "RenderSystem.hpp"
#include "CollisionSystem.hpp"
#include "CooldownSystem.hpp"
#include "GravitySystem.hpp"

void autoRegister(Registry& registry, Engine& engine) {
    registry.registerComponent<Collider>();
    registry.registerComponent<Cooldown>();
    registry.registerComponent<Enemy>();
    registry.registerComponent<Gravity>();
    registry.registerComponent<Health>();
    registry.registerComponent<MainPlayer>();
    registry.registerComponent<Position>();
    registry.registerComponent<Speed>();
    registry.registerComponent<Sprite>();
    registry.registerComponent<Velocity>();

    engine.registerSystem<InputSystem, MainPlayer, Position, Speed, Velocity, Cooldown>();
    engine.registerSystem<MovementSystem, Position, Velocity>();
    engine.registerSystem<RenderSystem, Position, Sprite>();
    engine.registerSystem<CollisionSystem, Position, Collider>();
    engine.registerSystem<CooldownSystem, Cooldown>();
    engine.registerSystem<GravitySystem, Position, Velocity, Gravity>();
}
