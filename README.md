# OpenGL C++ Project

Linux C++20 OpenGL starter project using GLFW for window management. GLEW 2.3.1 is also included and built locally for OpenGL extension loading.

## Dependencies

Installed system dependencies:

| Dependency | Version | Relevant path |
| --- | --- | --- |
| GCC / G++ | 13.3.0 | `/usr/bin/g++` |
| CMake | 4.4.4 | `/usr/bin/cmake` |
| GDB | System installed | Used by the VS Code debugger |
| GLFW runtime | 3.3.10-1build1 | `/usr/lib/x86_64-linux-gnu/libglfw.so.3` |
| GLFW development package | 3.3.10-1build1 | `/usr/include/GLFW/glfw3.h` |
| GLFW CMake package | 3.3.10-1build1 | `/usr/lib/x86_64-linux-gnu/cmake/glfw3/` |
| Mesa OpenGL development package | 25.2.8-0ubuntu0.24.04.4 | `/usr/lib/x86_64-linux-gnu/libOpenGL.so` |

The workspace copy of the GLFW linker library is:

```text
libraries/libglfw.so
```

GLEW source is located at:

```text
libraries/glew-2.3.1/
libraries/glew-2.3.1/include/GL/
```

## Built GLEW Artifacts

GLEW was built for Linux x86-64 with the bundled CMake project. The generated files are in:

```text
build/glew-linux/lib/libGLEW.so.2.3.1
build/glew-linux/lib/libGLEW.so.2.3
build/glew-linux/lib/libGLEW.so
build/glew-linux/lib/libGLEW.a
build/glew-linux/bin/glewinfo
build/glew-linux/bin/visualinfo
```

Rebuild GLEW with:

```bash
cmake -S libraries/glew-2.3.1/build/cmake \
  -B build/glew-linux \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_UTILS=ON \
  -DBUILD_SHARED_LIBS=ON
cmake --build build/glew-linux -j"$(nproc)"
```

## Build the Application

Configure and build the GLFW application from the project root:

```bash
cmake -S . -B build
cmake --build build
```

The executable is generated at:

```text
build/bin/opengl
```

Run it with:

```bash
./build/bin/opengl
```

The application source is [src/main.cpp](src/main.cpp). It creates an 800x600 GLFW window and renders a triangle using the compatibility OpenGL API.

## CMake Configuration

[CMakeLists.txt](CMakeLists.txt) configures:

- C++20 with extensions disabled
- GCC/Clang warnings: `-Wall -Wextra -Wpedantic`
- GLFW 3.3 or newer via `find_package(glfw3 3.3 REQUIRED)`
- OpenGL via `find_package(OpenGL REQUIRED)`
- Link targets `glfw` and `OpenGL::GL`
- `build/compile_commands.json` for IntelliSense

GLEW is built locally, but the application target does not currently link GLEW or call `glewInit()`. Add those when extension loading is needed.

## VS Code

Configured files:

```text
.vscode/settings.json
.vscode/tasks.json
.vscode/launch.json
.vscode/extensions.json
```

Use `Ctrl+Shift+B` to run the `CMake: build` task. The `Debug opengl` launch configuration builds the application and starts it with GDB.

VS Code IntelliSense reads:

```text
build/compile_commands.json
```

## Install Missing System Packages

On Ubuntu, install the system dependencies with:

```bash
sudo apt update
sudo apt install build-essential cmake gdb libglfw3-dev libgl1-mesa-dev
```