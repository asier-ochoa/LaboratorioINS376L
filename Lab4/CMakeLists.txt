add_executable(linkedList linkedList.cpp)
target_include_directories(linkedList PRIVATE ../include)
target_link_libraries(linkedList PRIVATE raylib $<TARGET_OBJECTS:rlImGui> $<TARGET_OBJECTS:imgui>)