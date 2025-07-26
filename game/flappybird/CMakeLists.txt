set(SRC
    main.cpp
)

add_executable(flappybird ${SRC})

add_subdirectory(auto)

target_link_libraries(flappybird 
    PUBLIC 
        core
)