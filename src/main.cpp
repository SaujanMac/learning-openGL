#include <cstdlib>

#define GLEW_NO_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

/**
 * @brief Parse a shader file and print the type of shader found (vertex or fragment).
 * @param filepath The path to the shader file.
 * @return A ShaderProgramSource struct containing the vertex and fragment shader source code.
 */
static ShaderProgramSource ParseShader(const std::string &filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2]; // 0: vertex, 1: fragment
    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {

            // Determine the type of shader based on the line content. If the line contains "vertex", set the type to VERTEX. If it contains "fragment", set the type to FRAGMENT.
            if (line.find("vertex") != std::string::npos)
            {

                type = ShaderType::VERTEX;
            }

            else if (line.find("fragment") != std::string::npos)
            {

                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            /**
             * if the line does not contain a shader type declaration, append it to the appropriate stringstream based on the current shader type. For example, if the current shader type is VERTEX, append the line to ss[0], and if it is FRAGMENT, append it to ss[1].
             */
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()}; // Return the vertex and fragment shader source code as a ShaderProgramSource struct
}
/**
 * @brief Compile a shader from source code and return its ID.
 * @param type The type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
 * @param source The source code of the shader.
 * @return The ID of the compiled shader, or 0 if compilation failed.
 */
static unsigned int CompileShader(unsigned int type, const std::string &source)
{
    unsigned int shaderID = glCreateShader(type); // create a shader object of the specified type (vertex or fragment)

    if (shaderID == 0)
    {
        std::cerr << "Error creating shader!" << std::endl;
        return 0;
    }

    const char *src = source.c_str();           // return a pointer to the underlying array of characters in the string.
    glShaderSource(shaderID, 1, &src, nullptr); // set the source code in shader
    glCompileShader(shaderID);                  // compile the shader

    // Check for compilation errors
    int success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        int length; // get the length of the error message
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char)); // allocate memory for the error message

        glGetShaderInfoLog(shaderID, length, &length, message); // get the error message

        std::cerr << "Failed to compile shader!" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cerr << message << std::endl;

        glDeleteShader(shaderID); // delete the shader object

        return 0;
    }

    return shaderID;
}

/**
 * @brief Create a shader program and return its ID.
 * @param vertexShaderSource The source code of the vertex shader.
 * @param fragmentShaderSource The source code of the fragment shader.
 * @return The ID of the created shader program, or 0 if creation failed.
 * 
*/
static unsigned int CreateShader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
{
    // Create a shader program
    unsigned int program = glCreateProgram();
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // Attach the compiled shaders to the program and link it
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    // Delete the shaders as they are no longer needed after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program; // Return the program ID
}

int main()
{
    if (!glfwInit())
    {
        return EXIT_FAILURE;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW after creating the OpenGL context. See https://glew.sourceforge.net/basic.html
    if (glewInit() != GLEW_OK)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    // Define the vertices for a triangle
    float vertices[] = {
        -0.5F, -0.5F,
        0.5F, -0.5F,
        0.5F, 0.5F,

        0.5F, 0.5F,
        -0.5F, 0.5F,
        -0.5F, -0.5F
    };

    unsigned int vbo;      // vbo object: Vertex Buffer Object
    glGenBuffers(1, &vbo); // get a vbo object

    // Bind the vbo object to the GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // use glBufferData to allocate memory for the buffer object
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), vertices, GL_STATIC_DRAW);

    // Enable the vertex attribute array for the position data
    glEnableVertexAttribArray(0);

    // Specify the layout of the vertex data
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    // Parse the shader file and get the vertex and fragment shader source code
    ShaderProgramSource shaderSource = ParseShader("assets/shaders/Basic.shader");
    


    unsigned int shaderProgram = CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource); // Create the shader program
    glUseProgram(shaderProgram); // Use the shader program

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.08F, 0.10F, 0.14F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        // Only draws the vbo object, which is bound to the GL_ARRAY_BUFFER target. See glBindBuffer above.
        glDrawArrays(GL_TRIANGLES, 0, 6); // Draw the triangle

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram); // Delete the shader program
    glDeleteBuffers(1, &vbo);       // Delete the VBO
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}