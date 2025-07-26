add_library(core
    src/Engine.cpp
)

target_include_directories(core PUBLIC
    includes
)
target_link_libraries(core 
    PUBLIC 
        raylib
        ecs
)
