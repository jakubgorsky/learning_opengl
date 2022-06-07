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

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
    window = glfwCreateWindow(960, 540, "ImGui!!!!", nullptr, nullptr);
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
        // img = 1293 x 1776
        float positions1[] = {
                200.0f, 200.0f, 0.0f, 0.0f,
                329.3f, 200.0f, 1.0f, 0.0f,
                329.3f, 377.6f, 1.0f, 1.0f,
                200.0f, 377.6f, 0.0f, 1.0f
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

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 100, 0));

        glm::mat4 mvp = proj * view * model;

        Shader shader("../res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 0.0f);
        shader.SetUniformMat4f("u_MVP", mvp);

        Texture tex("../res/textures/yerbaholic.png");
        tex.Bind();
        shader.SetUniform1i("u_Texture", 0);


        va.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;


        // IMGUI
        const char* glsl_version = "#version 330 core";
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init(glsl_version);

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

//        int r1, r2, g1, g2, b1, b2;
//        r1 = 100;
//        g1 = 0;
//        b1 = 0;
//        r2 = 0;
//        g2 = 100;
//        b2 = 0;
//        int increment = 5;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            shader.Bind();
//            shader.SetUniform4f("u_Color", (float) r1 / 100, (float) g1 / 100, (float) b1 / 100, 0.33f);
            renderer.Draw(va, ib, shader);
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            shader.Unbind();

            // rainbow effect
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

            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}