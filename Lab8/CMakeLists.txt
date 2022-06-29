add_executable(chessMoves chessMoves.cpp)
target_include_directories(chessMoves PRIVATE ../include)
target_link_libraries(chessMoves PRIVATE raylib $<TARGET_OBJECTS:rlImGui> $<TARGET_OBJECTS:imgui>)