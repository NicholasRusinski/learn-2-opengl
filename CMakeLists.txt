cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)

# Define Unicode flags
add_definitions(-DUNICODE -D_UNICODE)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include/glad)

# Add the source files
add_executable(OpenGLProject
    src/main.cpp
    src/window.cpp
    src/renderer.cpp
    src/glad.c)

# Link OpenGL (on Windows, you may need to manually specify opengl32)
find_package(OpenGL REQUIRED)
target_link_libraries(OpenGLProject OpenGL::GL OpenGL::GLU)

# Set the WIN32_EXECUTABLE property for the target
set_target_properties(OpenGLProject PROPERTIES WIN32_EXECUTABLE TRUE)

