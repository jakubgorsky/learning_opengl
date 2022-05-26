//
// Created by kubag on 19/05/2022.
//
#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"

class Renderer {
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
private:

};