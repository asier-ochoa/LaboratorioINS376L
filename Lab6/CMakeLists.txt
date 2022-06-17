add_executable(binaryTree binaryTree.cpp)
target_include_directories(binaryTree PRIVATE ../include)
target_link_libraries(binaryTree PRIVATE raylib $<TARGET_OBJECTS:rlImGui> $<TARGET_OBJECTS:imgui>)