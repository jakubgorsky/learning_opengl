//
// Created by kubag on 26/05/2022.
//

#include "GLErrorHandler.h"
#include <iostream>

void GLClearError(){
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line){
    while (GLenum error = glGetError()){
        std::cout << "[OpenGL ERROR] (" << error << ") in file " << file << " at line " << line << " caused by " << function  <<  std::endl;
        return false;
    }
    return true;
}