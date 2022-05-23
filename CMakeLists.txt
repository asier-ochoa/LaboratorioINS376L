cmake_minimum_required(VERSION 3.23)
project(LabINS)

set(CMAKE_CXX_STANDARD 17)

if(UNIX)
    add_compile_definitions(UNIX)
endif()
if(WIN32)
    add_compile_definitions(WIN32)
endif()


add_subdirectory(Lab1)
add_subdirectory(Lab2)
add_subdirectory(Lab3)