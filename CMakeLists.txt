cmake_minimum_required(VERSION 3.5.0)
project(pongc VERSION 0.3.0
              LANGUAGES C
              HOMEPAGE_URL https://github.com/xvitxr7/pongc
              DESCRIPTION "An overengineered Pong clone made in C using SDL2."
)

set(CMAKE_C_STANDARD_REQUIRED 99)
set(CMAKE_C_STANDARD 99)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

file(GLOB_RECURSE PC_SRC "src/*.c")

add_executable(pongc ${PC_SRC})
target_link_libraries(pongc PUBLIC SDL2 SDL2_image SDL2_ttf)
target_include_directories(pongc PUBLIC include)