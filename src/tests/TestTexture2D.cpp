//
// Created by kubag on 10/06/2022.
//

#include "TestTexture2D.h"

#include "imgui.h"


namespace test {

    TestTexture2D::TestTexture2D()
        : m_TranslationA(200, 200, 0), m_TranslationB(400, 400, 0),
        m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0)))
    {
        float positions[] = {
                0.0f, 0.0f, 0.0f, 0.0f,
                129.3f, 0.0f, 1.0f, 0.0f,
                129.3f, 177.6f, 1.0f, 1.0f,
                0.0f, 177.6f, 0.0f, 1.0f
        };
        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

        m_Shader = std::make_unique<Shader>("../res/shaders/Basic.shader");
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

        m_Texture = std::make_unique<Texture>("../res/textures/yerbaholic.png");
        m_Shader->SetUniform1i("u_Texture", 0);
    }

    void TestTexture2D::OnUpdate(float deltaTime) {
    }

    void TestTexture2D::OnRender() {

        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind();
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
    }

    void TestTexture2D::OnImGuiRender() {
        ImGui::Begin("Translation settings");
        ImGui::SliderFloat("Tranlsation Ax", &m_TranslationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat("Tranlsation Ay", &m_TranslationA.y, 0.0f, 540.0f);
        ImGui::SliderFloat("Tranlsation Bx", &m_TranslationB.x, 0.0f, 960.0f);
        ImGui::SliderFloat("Tranlsation By", &m_TranslationB.y, 0.0f, 540.0f);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::End();
    }
}