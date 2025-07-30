#include "Registry.hpp"
#include "Engine.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"
#include "Cooldown.hpp"
#include "Enemy.hpp"
#include "Gamepad.hpp"
#include "Gravity.hpp"
#include "Health.hpp"
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

void autoRegister(Registry& registry, Engine& engine) {
    registry.registerComponent<Bullet>();
    registry.registerComponent<Collider>();
    registry.registerComponent<Cooldown>();
    registry.registerComponent<Enemy>();
    registry.registerComponent<Gamepad>();
    registry.registerComponent<Gravity>();
    registry.registerComponent<Health>();
    registry.registerComponent<Position>();
    registry.registerComponent<Speed>();
    registry.registerComponent<Sprite>();
    registry.registerComponent<Time>();
    registry.registerComponent<Velocity>();

    engine.registerSystem<InputSystem, Gamepad, Position, Speed, Velocity, Cooldown>();
    engine.registerSystem<MovementSystem, Position, Velocity>();
    engine.registerSystem<RenderSystem, Position, Sprite>();
    engine.registerSystem<BulletSystem, Position, Bullet>();
    engine.registerSystem<CollisionSystem, Position, Collider>();
    engine.registerSystem<CooldownSystem, Cooldown>();
    engine.registerSystem<GravitySystem, Position, Velocity, Gravity>();
    engine.registerSystem<LifeSystem, Health>();
    engine.registerSystem<TimeSystem, Time>();
}
