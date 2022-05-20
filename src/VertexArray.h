//
// Created by kubag on 20/05/2022.
//

#ifndef OPENGL_VERTEXARRAY_H
#define OPENGL_VERTEXARRAY_H

#define DEF ~VertexArray()

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
    unsigned int m_RendererID;
public:
    VertexArray();

    virtual ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const;
    void Unbind() const;
};


#endif //OPENGL_VERTEXARRAY_H
