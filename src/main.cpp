#include <cstdlib>

#define GLEW_NO_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    if (!glfwInit()) {
        return EXIT_FAILURE;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW after creating the OpenGL context. See https://glew.sourceforge.net/basic.html
    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    // Define the vertices for a triangle
    float vertices[6] = {
        -0.5F, -0.5F,
         0.5F, -0.5F,
         0.5F,  0.5F
    };

    unsigned int vbo; // vbo object: Vertex Buffer Object
    glGenBuffers(1, &vbo); // get a vbo object

    // Bind the vbo object to the GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // use glBufferData to allocate memory for the buffer object
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.08F, 0.10F, 0.14F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        // Only draws the vbo object, which is bound to the GL_ARRAY_BUFFER target. See glBindBuffer above.
        glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle

        



        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}