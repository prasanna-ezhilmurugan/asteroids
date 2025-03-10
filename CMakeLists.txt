cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(DEBUG_COMPILE_OPTIONS "$<$<CONFIG:Debug>:-g;-Wall;-Wextra;-fsanitize=address,undefined>")
set(RELEASE_COMPILE_OPTIONS "$<$<CONFIG:Release>:-O3>")
set(COMPILE_OPTIONS
  ${DEBUG_COMPILE_OPTIONS}
  ${RELEASE_COMPILE_OPTIONS}
)

set(DEBUG_LINK_LIBRARIES "$<$<CONFIG:Debug>:asan;ubsan;m;SDL2;SDL2_image>")
set(RELEASE_LINK_LIBRARIES "$<$<CONFIG:Release>:>")
set(LINK_LIBRARIES
  ${DEBUG_LINK_LIBRARIES}
  ${RELEASE_LINK_LIBRARIES}
  ${SDL2_LIBRARIES}
)

project(asteroids)
add_executable(${PROJECT_NAME})


target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_LIBRARIES})
target_sources(${PROJECT_NAME} PRIVATE src/main.c src/game.c src/player.c src/utils.c)