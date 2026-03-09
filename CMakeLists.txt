cmake_minimum_required(VERSION 3.20)
project(fizika)

set(CMAKE_CXX_STANDARD 20)

# statikus build
set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_SHARED_LIBS OFF)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
)

FetchContent_MakeAvailable(SFML)

add_executable(fizika
        main.cpp
        toltesek.cpp
        tavolsag.h
)

target_link_libraries(fizika
        sfml-graphics
        sfml-window
        sfml-system
)
target_link_options(fizika PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
)