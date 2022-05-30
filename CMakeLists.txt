cmake_minimum_required(VERSION 3.21)
project(OpenGL)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Application.cpp
        src/Application.h
        src/Renderer.cpp
        src/Renderer.h
        src/VertexBuffer.cpp
        src/VertexBuffer.h
        src/IndexBuffer.cpp
        src/IndexBuffer.h
        src/VertexArray.cpp
        src/VertexArray.h
        src/VertexBufferLayout.cpp
        src/VertexBufferLayout.h
        src/Shader.cpp
        src/Shader.h
        src/GLErrorHandler.cpp
        src/GLErrorHandler.h
        src/vendor/stb_image/stb_image.h
        src/vendor/stb_image/stb_image.cpp
        src/Texture.cpp
        src/Texture.h
        )


add_compile_definitions(GLEW_STATIC)

include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/include)

link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-mingw)
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/lib/Release/x64)

add_executable(OpenGL ${SOURCE_FILES})

target_link_libraries(OpenGL glew32s glfw3 opengl32)