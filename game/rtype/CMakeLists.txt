set(SRC
    main.cpp
    src/InputAction.cpp
)

add_executable(rtype ${SRC})

target_include_directories(rtype 
    PUBLIC
        includes
)

target_link_libraries(rtype 
    PUBLIC 
        core
)

