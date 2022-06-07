cmake_minimum_required(VERSION 3.21)
project(OpenGL)

set(CMAKE_CXX_STANDARD 11)

add_compile_definitions(GLEW_STATIC)

include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include ${PROJECT_SOURCE_DIR}/Dependencies/GLEW/include ${PROJECT_SOURCE_DIR}/src/vendor ${PROJECT_SOURCE_DIR}/src/vendor/imgui)

set(STB_IMG_FILES
        src/vendor/stb_image/stb_image.cpp
        src/vendor/stb_image/stb_image.h)

FILE(GLOB IMGUI_FILES src/vendor/imgui/*.cpp src/vendor/imgui/*.h)

set(EXT_LIBS
        ${STB_IMG_FILES}
        ${IMGUI_FILES})

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
        src/Texture.cpp
        src/Texture.h
        src/imgui_impl_glfw.cpp
        src/imgui_impl_glfw.h
        )



link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-mingw ${PROJECT_SOURCE_DIR}/Dependencies/GLEW/lib/Release/x64)

add_executable(OpenGL ${SOURCE_FILES} ${EXT_LIBS})

target_link_libraries(OpenGL glew32s glfw3 opengl32)