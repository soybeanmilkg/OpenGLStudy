cmake_minimum_required(VERSION 3.28)

project(opengl)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd") # 设置运行时库为 MDd
endif()

# 依赖源文件
file(GLOB IMGUI_SOURCE dependencies/imgui/*.cpp)
file(GLOB GLAD_SOURCE dependencies/glad/src/*.c)
file(GLOB STB_SOURCE dependencies/stb/*.cpp)

set(REQUIRED_LIBS
    renderer

    glfw3
    opengl32
    user32
    gdi32
    shell32
)

include_directories(
    dependencies
    dependencies/glfw/include
    dependencies/glad/include

    renderer/src
)

link_directories(
    dependencies/glfw/lib
)

add_subdirectory(renderer)
add_subdirectory(sp01)
add_subdirectory(sp02)
