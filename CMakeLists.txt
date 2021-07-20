cmake_minimum_required(VERSION 3.19)
project(SlimeMoldSimulation)

set(CMAKE_CXX_STANDARD 17)
set(linkers -lglfw -lGL -lX11 -lpthread -lXrandr -ldl)
include_directories(include)

add_executable(SlimeMoldSimulation main.cpp glad.c Simulation.cpp Simulation.h Window.cpp Window.h Shader.h ComputeShader.h Texture.cpp Texture.h Sprite.cpp Sprite.h Framebuffer.cpp Framebuffer.h)
target_link_libraries(SlimeMoldSimulation ${linkers})