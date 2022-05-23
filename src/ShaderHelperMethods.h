//
// Created by kubag on 23/05/2022.
//

#ifndef OPENGL_SHADERHELPERMETHODS_H
#define OPENGL_SHADERHELPERMETHODS_H
#include <string>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
namespace SHM {
    struct ShaderProgramSource {
        std::string VertexSource;
        std::string FragmentSource;
    };
    ShaderProgramSource ParseShader(const std::string &filepath);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
}

#endif //OPENGL_SHADERHELPERMETHODS_H
