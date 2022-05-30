//
// Created by kubag on 30/05/2022.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "Renderer.h"

class Texture {
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const std::string &mFilePath);

    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    int GetHeight() const;

    int GetWidth() const;
};


#endif //OPENGL_TEXTURE_H
