add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/AutoRegister.cpp
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/generate_autoregister.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS components.txt systems.json generate_autoregister.py
)


add_library(autoregister AutoRegister.cpp)

target_include_directories(autoregister
    PUBLIC
        ../includes
        ../includes/systems
 
)

target_link_libraries(autoregister PUBLIC core)