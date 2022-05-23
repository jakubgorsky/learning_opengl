#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

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
    window = glfwCreateWindow(1024, 1024, "Abstracting OpenGL into classes", nullptr, nullptr);
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

        Shader shader("../res/shaders/Basic.shader");
        shader.Bind();

        shader.SetUniform4f("u_Color", 0.5f, 1.0f, 1.0f, 1.0f);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        int r, g, b;
        r = 100;
        g = 0;
        b = 0;
        int increment = 5;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            shader.Bind();
            shader.SetUniform4f("u_Color", (float) r / 100, (float) g / 100, (float) b / 100, 1.0f);

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
    }
    glfwTerminate();
    return 0;
}