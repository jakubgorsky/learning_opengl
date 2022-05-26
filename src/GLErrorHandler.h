
//
// Created by kubag on 26/05/2022.
//

#ifndef OPENGL_GLERRORHANDLER_H
#define OPENGL_GLERRORHANDLER_H

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(x); GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

#endif //OPENGL_GLERRORHANDLER_H
