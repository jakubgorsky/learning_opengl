//
// Created by kubag on 10/06/2022.
//

#include "TestSquare.h"

#include "imgui.h"

float test::TestSquare::m_Positions[8] = {
    0.0f, 0.0f,
    50.0f, 0.0f,
    50.0f, 50.0f,
    0.0f, 50.0f
};

unsigned int test::TestSquare::m_Indices[6] = {
        0, 1, 2,
        2, 3, 0
};

glm::vec3 test::TestSquare::translation(0,0,0);

test::TestSquare::TestSquare()
    : m_Color{1.0f, 1.0f, 1.0f, 1.0f},
    m_Renderer(),
    m_Shader("../res/shaders/Basic.shader"),
    m_Vb(m_Positions, 4 * 2 * sizeof(float)),
    m_Ib(m_Indices, 6)
    {
        m_Layout.Push<float>(2);
    }

test::TestSquare::~TestSquare() {
}

void test::TestSquare::OnUpdate(float deltaTime) {
}

void test::TestSquare::OnRender() {

    m_Va.AddBuffer(m_Vb, m_Layout);
    m_Shader.Bind();
    m_Shader.SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

    m_Va.Unbind();
    m_Vb.Unbind();
    m_Ib.Unbind();

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
    glm::mat4 mvp = proj * glm::mat4(1.0f) * model;

    m_Shader.SetUniformMat4f("u_MVP", mvp);

    m_Renderer.Draw(m_Va, m_Ib, m_Shader);
}

void test::TestSquare::OnImGuiRender() {
    ImGui::Text("Translation:");
    ImGui::SliderFloat("Tranlsation x", &translation.x, 0.0f, 960.0f);
    ImGui::SliderFloat("Tranlsation y", &translation.y, 0.0f, 540.0f);
    ImGui::Text("Color:");
    ImGui::ColorEdit4("Square color", m_Color);
}
