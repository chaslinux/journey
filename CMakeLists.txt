cmake_minimum_required(VERSION 3.25)

project(Journey
    VERSION 0.1.0
    DESCRIPTION "Journey - Land of the Undead"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Build SDL3 from our Git submodule.
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Journey executable.
add_executable(journey
    src/main.c
    src/renderer.c
    src/input.c
    src/map.c
    src/player.c
    src/camera.c
    src/dungeon.c
    src/game.c
    src/character.c
    src/monster.c
)

target_link_libraries(journey
    PRIVATE SDL3::SDL3
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(journey PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

