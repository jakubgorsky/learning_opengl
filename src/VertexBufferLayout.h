//
// Created by Jakub Górski on 20/05/2022.
//

#ifndef OPENGL_VERTEXBUFFERLAYOUT_H
#define OPENGL_VERTEXBUFFERLAYOUT_H

#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

struct VertexBufferElement{
    unsigned int type;
    GLint count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type){
        switch (type){
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    GLsizei m_Stride;
public:
    VertexBufferLayout()
        : m_Stride(0) {};
    template<typename T>
    void Push(GLint count){
    }
    inline std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }
};



template<>
inline void VertexBufferLayout::Push<float>(GLint count){
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(GLint count){
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}

template<>
inline void VertexBufferLayout::Push<unsigned char>(GLint count){
    m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}


#endif //OPENGL_VERTEXBUFFERLAYOUT_H
