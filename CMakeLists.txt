cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Fix for iOS builds: iOS needs single arch (arm64) while macOS needs both
# Using CACHE to ensure it overrides any previous value and matches SDK sysroots
if(APPLE)
    if(GEODE_TARGET_PLATFORM STREQUAL "iOS" OR CMAKE_SYSTEM_NAME STREQUAL "iOS")
        set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "" FORCE)
    else()
        set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "" FORCE)
    endif()
endif()
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(Gambling VERSION 2.0.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})
