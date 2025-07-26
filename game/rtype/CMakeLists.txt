set(SRC
    main.cpp
    src/InputAction.cpp
    src/ReactionSystem.cpp
)

add_executable(rtype ${SRC})

add_subdirectory(auto)

target_include_directories(rtype 
    PUBLIC
        includes
)

target_link_libraries(rtype 
    PUBLIC 
        core
)

