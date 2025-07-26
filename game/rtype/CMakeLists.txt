add_subdirectory(auto)

set(SRC
    main.cpp
    src/InputAction.cpp
    src/ReactionSystem.cpp
    src/systems/BulletSystem.cpp
)

add_executable(rtype ${SRC})

target_include_directories(rtype 
    PUBLIC
        includes
        includes/systems
)

target_link_libraries(rtype 
    PUBLIC
        core
        ecs
        autoregister
)

