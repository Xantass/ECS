#include "Registry.hpp"
#include "Engine.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"
#include "Cooldown.hpp"
#include "Enemy.hpp"
#include "Gamepad.hpp"
#include "Gravity.hpp"
#include "Health.hpp"
#include "MainPlayer.hpp"
#include "Position.hpp"
#include "Speed.hpp"
#include "Sprite.hpp"
#include "Time.hpp"
#include "Velocity.hpp"
#include "InputSystem.hpp"
#include "MovementSystem.hpp"
#include "RenderSystem.hpp"
#include "BulletSystem.hpp"
#include "CollisionSystem.hpp"
#include "CooldownSystem.hpp"
#include "GravitySystem.hpp"
#include "LifeSystem.hpp"
#include "TimeSystem.hpp"
#include "ResetVelocitySystem.hpp"

void autoRegister(Registry& registry, Engine& engine) {
    registry.registerComponent<Bullet>();
    registry.registerComponent<Collider>();
    registry.registerComponent<Cooldown>();
    registry.registerComponent<Enemy>();
    registry.registerComponent<Gamepad>();
    registry.registerComponent<Gravity>();
    registry.registerComponent<Health>();
    registry.registerComponent<MainPlayer>();
    registry.registerComponent<Position>();
    registry.registerComponent<Speed>();
    registry.registerComponent<Sprite>();
    registry.registerComponent<Time>();
    registry.registerComponent<Velocity>();

    engine.registerSystem<InputSystem>();
    engine.registerSystem<MovementSystem>();
    auto& renderSystem = engine.registerSystem<RenderSystem>();
    engine.setRenderSystem(&renderSystem);
    engine.registerSystem<BulletSystem>();
    engine.registerSystem<CollisionSystem>();
    engine.registerSystem<CooldownSystem>();
    engine.registerSystem<GravitySystem>();
    engine.registerSystem<LifeSystem>();
    engine.registerSystem<TimeSystem>();
    engine.registerSystem<ResetVelocitySystem>();
}
