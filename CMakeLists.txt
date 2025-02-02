cmake_minimum_required(VERSION 3.22)

project(Carbonite)

add_subdirectory(Lib/EnTT)
add_subdirectory(Lib/SDL)
add_subdirectory(Lib/spdlog)
add_subdirectory(Lib/glm)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

set(SRC
        Source/Carbonite.cpp
        Source/Init.cpp
        Source/Init.hpp
        Source/Event.cpp
        Source/Event.hpp
        Source/Random.cpp
        Source/Random.hpp
        Source/Input.cpp
        Source/Input.hpp
        Source/Math.cpp
        Source/Math.hpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SRC})

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog SDL2::SDL2 EnTT::EnTT glm::glm)
