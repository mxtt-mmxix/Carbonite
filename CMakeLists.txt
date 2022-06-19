cmake_minimum_required(VERSION 3.22)

project(Carbonite)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

set(SRC
    Source/Carbonite.cpp Source/Engine.cpp Source/Engine.hpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SRC})

add_library(${PROJECT_NAME} ${SRC})
