//
// Created by kubag on 23/05/2022.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <string>
#include <GL/glew.h>
#include <bits/stdc++.h>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader {
private:
    std::string m_FilePath{};
    unsigned int m_RendererID{};

    static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    static unsigned int CompileShader(unsigned int type, const std::string& source);
    static ShaderProgramSource ParseShader(const std::string &filepath);
    std::unordered_map<std::string, int> m_UniformLocationCache;

    unsigned int GetUniformLocation(const std::string& name);
public:
    explicit Shader(const std::string& filepath);
    ~Shader();
    void Bind() const;
    void Unbind() const;

    // set uniforms
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
};

#endif //OPENGL_SHADER_H
