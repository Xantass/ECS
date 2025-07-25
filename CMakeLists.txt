cmake_minimum_required(VERSION 3.16)
project(RTypeEngine)

# Politique pour compatibilité avec projets CMake anciens (ex: Raylib 4.5.0)
cmake_policy(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include CPM (auto-package manager)
include(cmake/CPM.cmake)

# === Raylib ===
CPMAddPackage(
  NAME raylib
  GITHUB_REPOSITORY raysan5/raylib
  GIT_TAG master         # ou GIT_TAG 4.5.0 si rétrocompatibilité + cmake_policy
  OPTIONS "BUILD_EXAMPLES OFF" "BUILD_GAMES OFF"
)

# Active les warnings utiles
if (MSVC)
    add_compile_options(/W4 /WX)
    target_compile_options(raylib PRIVATE /w)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    target_compile_options(raylib PRIVATE -w)
endif()

# === Sous-projet du moteur ===
add_subdirectory(engine)
add_subdirectory(ecs)

if(GAME STREQUAL "rtype")
    add_subdirectory(game/rtype)
elseif(GAME STREQUAL "flappybird")
    add_subdirectory(game/flappybird)
endif()
