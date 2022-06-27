cmake_minimum_required(VERSION 3.23)
project(LabINS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
find_package(raylib 4.0.0 QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

add_subdirectory(libs/imgui)
add_subdirectory(libs/rlImGui)

if(UNIX)
    add_compile_definitions(UNIX)
endif()
if(WIN32)
    add_compile_definitions(WIN32)
endif()


add_subdirectory(Lab1)
add_subdirectory(Lab2)
add_subdirectory(Lab3)
add_subdirectory(Lab4)
add_subdirectory(Lab5)
add_subdirectory(Lab6)
add_subdirectory(Lab7)
