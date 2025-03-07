cmake_minimum_required(VERSION 3.20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_LIBARIES})

project(asteroids)
add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(${PROJECT_NAME} PRIVATE src/main.c)
