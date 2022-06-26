add_executable(hanoiTower hanoiTower.cpp)
target_include_directories(hanoiTower PRIVATE ../include)
target_link_libraries(hanoiTower PRIVATE raylib $<TARGET_OBJECTS:rlImGui> $<TARGET_OBJECTS:imgui>)