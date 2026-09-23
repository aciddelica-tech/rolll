cmake_minimum_required(VERSION 3.22)
project(rolll LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED VDJ_SDK_DIR)
    message(FATAL_ERROR "VDJ_SDK_DIR is not set")
endif()

find_path(VDJ_SDK_INCLUDE_DIR
    NAMES vdjPlugin8.h vdjDsp8.h
    PATHS "${VDJ_SDK_DIR}"
    PATH_SUFFIXES Include include
    NO_DEFAULT_PATH)

if(NOT VDJ_SDK_INCLUDE_DIR)
    message(FATAL_ERROR "VirtualDJ SDK headers were not found in ${VDJ_SDK_DIR}")
endif()

add_library(rolll SHARED Main.cpp LoopRoll.cpp)
target_include_directories(rolll PRIVATE "${VDJ_SDK_INCLUDE_DIR}")
target_compile_definitions(rolll PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
set_target_properties(rolll PROPERTIES OUTPUT_NAME "rolll" PREFIX "" SUFFIX ".dll")

if(MSVC)
    target_compile_options(rolll PRIVATE /W4 /EHsc)
    target_link_options(rolll PRIVATE /EXPORT:DllGetClassObject)
endif()
