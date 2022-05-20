#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath){
    std::ifstream stream(filepath);

    enum class ShaderType{
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)){
        if (line.find("#shader") != std::string::npos){
            if (line.find("vertex") != std::string::npos){
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos){
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return  { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result{};
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE){
        int length{};
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader failed to compile. [ERR MESSAGE]: " << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(600, 600, "OpenGL Shader Learning", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current  */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewInit();

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
                0.0f, 0.0f,
                -0.6f, 0.0f,
                -0.3f, -0.6f,
                0.3f, -0.6f,
                0.6f, 0.0f,
                0.3f, 0.6f,
                -0.3f, 0.6f
        };

        unsigned int indices[] = {
                0, 1, 2,
                0, 2, 3,
                0, 3, 4,
                0, 4, 5,
                0, 5, 6,
                0, 6, 1
        };

        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        VertexArray va;
        VertexBuffer vb(positions, 14 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 18);

        ShaderProgramSource source = ParseShader("../res/shaders/Basic.shader");

        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        glUseProgram(shader);

        GLCall(int location = glGetUniformLocation(shader, "u_Color"));
        ASSERT(location != -1);
        GLCall(glUniform4f(location, 0.5f, 1.0f, 1.0f, 1.0f));

        GLCall(glBindVertexArray(0));
        GLCall(glUseProgram(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));


        int r, g, b;
        r = 100;
        g = 0;
        b = 0;
        int increment = 5;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            GLCall(glUseProgram(shader));
            GLCall(glUniform4f(location, (float) r / 100, (float) g / 100, (float) b / 100, 1.0f));

            va.Bind();
            ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr));

            // rainbow effect
            if (r == 100 && g < 100 && b == 0) {
                g += increment;
            } else if (r > 0 && g == 100 && b == 0) {
                r -= increment;
            } else if (r == 0 && g == 100 && b < 100) {
                b += increment;
            } else if (r == 0 && g > 0 && b == 100) {
                g -= increment;
            } else if (r < 100 && g == 0 && b == 100) {
                r += increment;
            } else if (r == 100 && g == 0 && b > 0) {
                b -= increment;
            }

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glDeleteProgram(shader);
    }
    glfwTerminate();
    return 0;
}