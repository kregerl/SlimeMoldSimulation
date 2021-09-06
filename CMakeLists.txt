cmake_minimum_required(VERSION 3.19)
project(SlimeMoldSimulation)

find_package(OpenGL REQUIRED)

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


set(SOURCE_FILES src/main.cpp glad/src/glad.c src/Simulation.cpp src/Simulation.h src/Window.cpp src/Window.h src/Shader.h src/ComputeShader.h src/Texture.cpp src/Texture.h src/Sprite.cpp src/Sprite.h src/Framebuffer.cpp src/Framebuffer.h src/Settings.cpp src/Settings.h include/stb_image.cpp src/AgentSystem.cpp src/AgentSystem.h)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Linking GLFW and OGL
target_link_libraries(${CMAKE_PROJECT_NAME}  glfw glm imgui yaml-cpp ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})
add_custom_target(copy-shaders ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        ${CMAKE_CURRENT_BINARY_DIR}/shaders)
add_custom_target(copy-assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/images
        ${CMAKE_CURRENT_BINARY_DIR}/images)
add_dependencies(${CMAKE_PROJECT_NAME} copy-shaders)
add_dependencies(${CMAKE_PROJECT_NAME} copy-assets)
