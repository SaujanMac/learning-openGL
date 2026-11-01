# Drawing a Triangle with OpenGL (Hello Triangle)
This project demonstrates how to draw a triangle using OpenGL with GLFW and GLEW. It creates a window and renders a triangle using the compatibility OpenGL API.

## Prerequisites
- CMake
- A C++ compiler that supports C++11 or later
- GLFW library
- GLEW library

# Steps To Build and Run
## Step 1: Create a GLFW Window
The application creates an 800x600 GLFW window.

```cpp
// Create a GLFW window
int main(){
if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
}

GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
}

// Make the window's context current
glfwMakeContextCurrent(window);

}
```
## Step 2: Initialize GLEW
After creating the window, initialize GLEW to load OpenGL function pointers.

### What is GLEW?
GLEW (OpenGL Extension Wrangler Library) is a cross-platform open-source C/C++ extension loading library. It provides efficient run-time mechanisms for determining which OpenGL extensions are supported on the target platform. GLEW is used to access modern OpenGL functionality that may not be available in the default OpenGL headers provided by the system.

```cpp

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(window); // Clean up the window
        glfwTerminate(); // Terminate GLFW
        return -1;
    }

```

## Step 3: Set Up Vertex Data
Define the vertices of the triangle and set up a Vertex Buffer Object (VBO) to store the vertex data on the GPU.

```cpp
float vertices[] = {
    -0.5f, -0.5f, // Bottom left
     0.5f, -0.5f, // Bottom right
     0.0f,  0.5f  // Top center
};

unsigned int vbo; // Vertex Buffer Object
glGenBuffers(1, &vbo); // Generate a VBO
glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind the VBO to the GL_ARRAY_BUFFER target
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Upload the vertex data to the GPU

// Enable the vertex attribute array and specify the layout of the vertex data
glEnableVertexAttribArray(0); // Enable the first attribute (position)
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 *sizeof(float), (void*)0); // Specify the layout of the vertex data
```
## Step 4: Render the Triangle
In the main loop, clear the screen and draw the triangle using `glDrawArrays`.

```cpp
while (!glfwWindowShouldClose(window)) {
    // Clear the screen
    glClearColor(0.08f, 0.10f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle using the vertex data in the VBO

    // Swap front and back buffers
    glfwSwapBuffers(window);
    // Poll for and process events
    glfwPollEvents();
}
```