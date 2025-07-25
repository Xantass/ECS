set(SRC
    src/Registry.cpp
    src/systems/BulletSystem.cpp
    src/systems/CollisionSystem.cpp
    src/systems/CooldownSystem.cpp
    src/systems/GravitySystem.cpp
    src/systems/InputSystem.cpp
    src/systems/MovementSystem.cpp
    src/systems/RenderSystem.cpp
)

add_library(ecs ${SRC})

add_subdirectory(auto)

target_include_directories(ecs 
    PUBLIC
        includes
        includes/components
        includes/events
        includes/systems
)
target_link_libraries(ecs PUBLIC core)


