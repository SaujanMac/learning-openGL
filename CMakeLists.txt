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

set(GLEW_ROOT "${CMAKE_SOURCE_DIR}/libraries/glew-2.3.1")
set(GLEW_LIBRARY "${CMAKE_SOURCE_DIR}/build/glew-linux/lib/libGLEW.so.2.3.1")

if(NOT EXISTS "${GLEW_LIBRARY}")
    message(FATAL_ERROR "GLEW library not found at ${GLEW_LIBRARY}. Build GLEW first.")
endif()

add_library(glew_local SHARED IMPORTED GLOBAL)
set_target_properties(glew_local PROPERTIES
    IMPORTED_LOCATION "${GLEW_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${GLEW_ROOT}/include"
)

add_executable(opengl
    src/main.cpp
)

target_link_libraries(opengl PRIVATE
    glfw
    glew_local
    OpenGL::GL
)

target_compile_options(opengl PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic>
)

set_target_properties(opengl PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    BUILD_RPATH "${CMAKE_SOURCE_DIR}/build/glew-linux/lib"
)