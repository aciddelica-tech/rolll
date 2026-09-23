cmake_minimum_required(VERSION 3.20)

project(rolll LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(rolll SHARED
    LoopRoll.cpp
)

target_include_directories(rolll PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(MSVC)
    target_compile_options(rolll PRIVATE /W4)
else()
    target_compile_options(rolll PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(rolll PROPERTIES
    OUTPUT_NAME "rolll"
)
