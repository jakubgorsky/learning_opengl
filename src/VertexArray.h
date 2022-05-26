//
// Created by Jakub Górski on 20/05/2022.
//

#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
    unsigned int m_RendererID;
public:
    VertexArray();

    virtual ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const;

    void Bind() const;
    void Unbind() const;
};