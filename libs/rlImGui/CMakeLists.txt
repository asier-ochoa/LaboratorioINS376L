file(GLOB SRC *.cpp)
add_library(rlImGui ${SRC})
target_link_libraries(rlImGui raylib imgui)
target_include_directories(rlImGui PRIVATE ../../include)
