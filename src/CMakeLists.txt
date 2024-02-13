cmake_minimum_required(VERSION 3.24)
project(3dengine)

set(CMAKE_CXX_STANDARD 17)

# you might need to do something else if you do not or cannot install glfw
find_package(glfw3 REQUIRED)

add_library(glad STATIC ../lib/glad/src/glad.c)
target_include_directories(glad PRIVATE ../lib/glad/include)

include_directories(../lib/stb_image/include)
include_directories(../lib/glm)

add_executable(3dengine main.cpp
        Shader.cpp
        utils.cpp
        VertexArray.cpp
        ObjectBuffer.cpp
        Texture.cpp
        Camera.cpp
        Mesh.cpp
)

target_link_libraries(3dengine PRIVATE glfw glad)

target_include_directories(3dengine PRIVATE ${GLFW_INCLUDE_DIRS} ../lib/glad/include)