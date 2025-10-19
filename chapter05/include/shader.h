#pragma once

#include "glad/gl.h"
#include <string>

class Shader {
public:
    Shader();
    ~Shader();

    bool Load(const std::string& vertName, const std::string& fragName);
    void SetActive();

private:
    bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShaderId);
    bool IsCompiled(GLuint shaderId);
    bool IsValidProgram();

    GLuint mVertShaderId;
    GLuint mFragShaderId;
    GLuint mShaderProgramId;
};
