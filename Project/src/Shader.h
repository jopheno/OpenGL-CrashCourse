#pragma once

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include "Common.h"

#include "DirectionalLight.h"
#include "SpotLight.h"

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
    GLuint GetSpecularIntensityLocation();
    GLuint GetShininessLocation();
    GLuint GetEyePositionLocation();
    
    void SetDirectionalLight(DirectionalLight* dLight);
    void SetPointLights(PointLight* pLight, unsigned int lightCount);
    void SetSpotLights(SpotLight* sLight, unsigned int lightCount);
    
    void Use();
    void Clear();
    
private:
    int pointLightCount, spotLightCount;

    GLuint shaderId, uniformProjection, uniformModel, uniformView, uniformEyePosition,
    uniformSpecularIntensity, uniformShininess;
    
    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
        
        GLuint uniformDirection;
    } uniformDirectionalLight;
    
    GLuint uniformPointLightCount;
    
    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
        
        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;
    } uniformPointLight[MAX_POINT_LIGHTS];
    
    GLuint uniformSpotLightCount;

    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
        
        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;
        
        GLuint uniformDirection;
        GLuint uniformEdge;
    } uniformSpotLight[MAX_SPOT_LIGHTS];
    
    void CompileShader(const char* vertexShaderCode, const char* fragmentShaderCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
    
    std::string ReadFile(const char* fileLocation);
};
