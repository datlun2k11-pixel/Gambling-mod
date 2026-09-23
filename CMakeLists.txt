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

# Patch bindings to fix pugi::xml_node destructor for clang 21 (issue with bindings main on SDK 5.10.1)
# The inline destructor definition fails on newer clang because pugixml header doesn't declare it
# We remove the inline declaration and empty the inline file to avoid both compile and linker errors
if (DEFINED ENV{GEODE_BINDINGS_REPO_PATH})
    set(BINDINGS_BRO "$ENV{GEODE_BINDINGS_REPO_PATH}/bindings/2.2081/Cocos2d.bro")
    set(BINDINGS_INLINE "$ENV{GEODE_BINDINGS_REPO_PATH}/bindings/2.2081/inline/xml_node.cpp")
    if (EXISTS "${BINDINGS_BRO}")
        file(READ "${BINDINGS_BRO}" BRO_CONTENT)
        string(REPLACE "    ~xml_node() = inline;\n" "" BRO_CONTENT "${BRO_CONTENT}")
        file(WRITE "${BINDINGS_BRO}" "${BRO_CONTENT}")
        message(STATUS "Patched ${BINDINGS_BRO} to remove xml_node dtor")
    endif()
    if (EXISTS "${BINDINGS_INLINE}")
        file(WRITE "${BINDINGS_INLINE}" "// patched - xml_node destructor removed for clang 21 compatibility\n")
        message(STATUS "Patched ${BINDINGS_INLINE}")
    endif()
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})
