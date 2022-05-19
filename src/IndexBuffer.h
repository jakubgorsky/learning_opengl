//
// Created by kubag on 19/05/2022.
//

#ifndef OPENGL_INDEXBUFFER_H
#define OPENGL_INDEXBUFFER_H


class IndexBuffer {
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
};



#endif //OPENGL_INDEXBUFFER_H
