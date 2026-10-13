#include <cstdlib>

#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        return EXIT_FAILURE;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.08F, 0.10F, 0.14F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);

        glVertex2f(-0.5F, -0.5F);
        glVertex2f(0.5F, -0.5F);
        glVertex2f(0.5F, 0.5F);
        
        glEnd();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}