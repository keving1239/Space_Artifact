cmake_minimum_required(VERSION 3.17)
project(spaceArtifact)



link_libraries(cs4722 glfw3 opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib ../lib-common)
link_directories(lib ../lib-common)

add_executable(spaceArtifact simulation/simulation.cpp)
configure_file(simulation/fragment_shader.glsl .)
configure_file(simulation/vertex_shader.glsl .)