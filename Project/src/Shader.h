#pragma once

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader {
public:
    Shader();
    ~Shader();
    
    void CreateFromString(const char* vertexShaderCode, const char* fragmentShaderCode);
    void CreateFromFiles(const char* vertexFileLocation, const char* fragmentFileLocation);
    
    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();

    GLuint GetAmbientIntensityLocation();
    GLuint GetColourLocation();
    GLuint GetDiffuseIntensityLocation();
    GLuint GetDirectionLocation();
    
    void Use();
    void Clear();
    
private:
    GLuint shaderId, uniformProjection, uniformModel, uniformView,
    uniformAmbientIntensity, uniformColour, uniformDiffuseIntensity, uniformDirection;
    
    void CompileShader(const char* vertexShaderCode, const char* fragmentShaderCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
    
    std::string ReadFile(const char* fileLocation);
};
