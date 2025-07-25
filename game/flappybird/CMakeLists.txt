set(SRC
    main.cpp
)

add_executable(flappybird ${SRC})

target_link_libraries(flappybird 
    PUBLIC 
        core
)