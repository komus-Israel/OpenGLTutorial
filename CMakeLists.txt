cmake_minimum_required(VERSION 3.0.0)
project(opengl_project VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)

add_executable(opengl_project 
    src/main.cpp
    src/glad/glad.c
)

target_link_libraries(opengl_project
    glfw
    GL
    X11
    pthread
    Xrandr
    Xi
    dl
)
