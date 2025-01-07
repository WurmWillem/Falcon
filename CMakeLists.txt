cmake_minimum_required(VERSION 3.30)

project(
    FalconTextEditor
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wpedantic -lncurses")

# all files in falcon/ are needed for FalconLib
file(GLOB FALCON_SRC
     "editor/*.hpp"
     "editor/*.cpp"
)
add_library(FalconLib ${FALCON_SRC})

add_executable(falcon main.cpp)

target_link_libraries(falcon PRIVATE FalconLib)
