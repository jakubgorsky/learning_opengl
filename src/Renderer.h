//
// Created by kubag on 19/05/2022.
//

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(x); GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer {

};


#endif //OPENGL_RENDERER_H
