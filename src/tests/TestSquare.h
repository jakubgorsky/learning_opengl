//
// Created by kubag on 10/06/2022.
//

#ifndef OPENGL_TESTSQUARE_H
#define OPENGL_TESTSQUARE_H

#include "Test.h"

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test{

    class TestSquare : public Test {
    public:
        explicit TestSquare();
        ~TestSquare();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        Renderer m_Renderer;
        Shader m_Shader;
        VertexArray m_Va;
        VertexBuffer m_Vb;
        VertexBufferLayout m_Layout;
        IndexBuffer m_Ib;

        float m_Color[4];
        static glm::vec3 translation;
        static float m_Positions[8];
        static unsigned int m_Indices[6];
    };

}

#endif //OPENGL_TESTSQUARE_H
