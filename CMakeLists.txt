cmake_minimum_required(VERSION 3.20)

project(opengl
    VERSION 0.1.0
    DESCRIPTION "C++ project"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(opengl
    src/main.cpp
)

target_link_libraries(opengl PRIVATE
    glfw
    OpenGL::GL
)

target_compile_options(opengl PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic>
)

set_target_properties(opengl PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)