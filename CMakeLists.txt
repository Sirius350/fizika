cmake_minimum_required(VERSION 4.1)
project(fizika)

set(CMAKE_CXX_STANDARD 20)

add_executable(fizika main.cpp
        toltesek.h)





include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
)

FetchContent_MakeAvailable(SFML)



target_link_libraries(fizika
        SFML::Graphics
)