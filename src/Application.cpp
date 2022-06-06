#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

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
    glfwSwapInterval(4);

    glewInit();

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions1[] = {
                -0.5f, -0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
                0, 1, 2,
                0, 2, 3,
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        VertexArray va;
        VertexBuffer vb(positions1, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);


        Shader shader("../res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 0.0f);
        shader.SetUniformMat4f("u_MVP", proj);

        Texture tex("../res/textures/yerbaholic.png");
        tex.Bind();
        shader.SetUniform1i("u_Texture", 0);


        va.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        int r1, r2, g1, g2, b1, b2;
        r1 = 100;
        g1 = 0;
        b1 = 0;
        r2 = 0;
        g2 = 100;
        b2 = 0;
        int increment = 5;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.Clear();

            shader.Bind();
//            shader.SetUniform4f("u_Color", (float) r1 / 100, (float) g1 / 100, (float) b1 / 100, 0.33f);
            renderer.Draw(va, ib, shader);
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            shader.Unbind();

//            // rainbow effect
//            if (r1 == 100 && g1 < 100 && b1 == 0) {
//                g1 += increment;
//            } else if (r1 > 0 && g1 == 100 && b1 == 0) {
//                r1 -= increment;
//            } else if (r1 == 0 && g1 == 100 && b1 < 100) {
//                b1 += increment;
//            } else if (r1 == 0&& g1 > 0 && b1 == 100) {
//                g1 -= increment;
//            } else if (r1 < 100 && g1 == 0 && b1 == 100) {
//                r1 += increment;
//            } else if (r1 == 100 && g1 == 0 && b1 > 0) {
//                b1 -= increment;
//            }

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}