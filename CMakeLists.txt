cmake_minimum_required(VERSION 3.19)
project(SlimeMoldSimulation)

find_package(OpenGL REQUIRED)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

# Including GLFW
add_subdirectory(glfw)
include_directories(glfw/include)

add_subdirectory(glm)
include_directories(glm/glm)

# Including GLAD
include_directories(glad/include)

# imgui
add_subdirectory(imgui)
include_directories(imgui)

#YAML-cpp
add_subdirectory(yaml-cpp)
include_directories(yaml-cpp)

include_directories(include)

set(SOURCE_FILES main.cpp glad/src/glad.c Simulation.cpp Simulation.h Window.cpp Window.h Shader.h ComputeShader.h Texture.cpp Texture.h Sprite.cpp Sprite.h Framebuffer.cpp Framebuffer.h Settings.cpp Settings.h include/stb_image.cpp AgentSystem.cpp AgentSystem.h)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Linking GLFW and OGL
target_link_libraries(${CMAKE_PROJECT_NAME}  glfw glm imgui yaml-cpp ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

