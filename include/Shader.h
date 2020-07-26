#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <GL/glew.h>

namespace test {

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
    private:
        std::string m_FilePath;
        mutable std::unordered_map<std::string, int> m_UniformLocationCache;

    public:
        Shader(const std::string& filePath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        // Set uniforms
        void SetUniform1i(const std::string& name, int i0);
        void SetUniform1f(const std::string& name, float v0);
        void SetUniform2f(const std::string& name, float v0, float v1);
        void SetUniform3f(const std::string& name, float v0, float v1, float v2);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUniform3fv(const std::string& name, int count, const float* value);
        void SetUniform4fv(const std::string& name, int count, const float* value);
        void SetUniformMatrix4fv(const std::string& name, int count, bool transpose, const float* value);
    
        unsigned int m_RendererID;

    private:
        ShaderProgramSource ParseShader(const std::string& filePath);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

        int GetUniformLocation(const std::string& name) const;
};

}

