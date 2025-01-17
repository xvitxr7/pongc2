cmake_minimum_required(VERSION 3.5.0)
project(pongc VERSION 0.3.0
              LANGUAGES C
              HOMEPAGE_URL https://github.com/xvitxr7/pongc2
              DESCRIPTION "An overengineered Pong clone made in C using SDL2."
)

set(CMAKE_C_STANDARD_REQUIRED 99)
set(CMAKE_C_STANDARD 99)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

file(GLOB_RECURSE PC_SRC "src/*.c")

add_executable(pongc ${PC_SRC})

# find_package(json-c CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
target_link_libraries(pongc PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)
target_include_directories(pongc PUBLIC include)