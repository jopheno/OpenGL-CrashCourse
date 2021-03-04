#include <cstdio>

#include "Shader.h"

Shader::Shader(): shaderId(0), uniformProjection(0), uniformModel(0), uniformView(0), pointLightCount(0) {}

Shader::~Shader() {
    Clear();
}

std::string Shader::ReadFile(const char* fileLocation) {
    std::string content;
    
    std::ifstream fileStream(fileLocation, std::ios::in);
    
    if(!fileStream.is_open()) {
        printf("Failed to read %s! File doesn't exist.", fileLocation);
        return "";
    }
    
    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + '\n');
    }
    
    fileStream.close();

    return content;
}

void Shader::CreateFromFiles(const char* vertexFileLocation, const char* fragmentFileLocation) {
    std::string vertexShaderCodeStr = ReadFile(vertexFileLocation);
    std::string fragmentShaderCodeStr = ReadFile(fragmentFileLocation);
    
    CompileShader(vertexShaderCodeStr.c_str(), fragmentShaderCodeStr.c_str());
}

void Shader::CreateFromString(const char *vertexShaderCode, const char *fragmentShaderCode) {
    CompileShader(vertexShaderCode, fragmentShaderCode);
}

void Shader::Use() {
    glUseProgram(shaderId);
}

void Shader::Clear() {
    if (shaderId != 0) {
        glDeleteProgram(shaderId);
        shaderId = 0;
    }
    
    uniformModel = 0;
    uniformProjection = 0;
    uniformView = 0;
}

GLuint Shader::GetProjectionLocation() {
    return uniformProjection;
}

GLuint Shader::GetModelLocation(){
    return uniformModel;
}

GLuint Shader::GetViewLocation(){
    return uniformView;
}

GLuint Shader::GetColourLocation() {
    return uniformDirectionalLight.uniformColour;
}

GLuint Shader::GetAmbientIntensityLocation() {
    return uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::GetDiffuseIntensityLocation() {
    return uniformDirectionalLight.uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation() {
    return uniformDirectionalLight.uniformDirection;
}

GLuint Shader::GetSpecularIntensityLocation() {
    return uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation() {
    return uniformShininess;
}

GLuint Shader::GetEyePositionLocation() {
    return uniformEyePosition;
}

void Shader::SetDirectionalLight(DirectionalLight *dLight) {
    dLight->Use(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColour, uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformDirection);
}

void Shader::SetPointLights(PointLight* pLight, unsigned int lightCount) {
    if (lightCount > MAX_POINT_LIGHTS)
        lightCount = MAX_POINT_LIGHTS;
    
    glUniform1i(uniformPointLightCount, lightCount);
    
    for (size_t i = 0; i < lightCount; i++) {
        pLight[i].Use(uniformPointLight[i].uniformAmbientIntensity, uniformPointLight[i].uniformColour, uniformPointLight[i].uniformDiffuseIntensity, uniformPointLight[i].uniformPosition, uniformPointLight[i].uniformConstant, uniformPointLight[i].uniformLinear, uniformPointLight[i].uniformExponent);
    }
}

void Shader::SetSpotLights(SpotLight* sLight, unsigned int lightCount) {
    if (lightCount > MAX_SPOT_LIGHTS)
        lightCount = MAX_SPOT_LIGHTS;
    
    glUniform1i(uniformSpotLightCount, lightCount);
    
    for (size_t i = 0; i < lightCount; i++) {
        sLight[i].Use(uniformSpotLight[i].uniformAmbientIntensity, uniformSpotLight[i].uniformColour, uniformSpotLight[i].uniformDiffuseIntensity, uniformSpotLight[i].uniformPosition, uniformSpotLight[i].uniformConstant, uniformSpotLight[i].uniformLinear, uniformSpotLight[i].uniformExponent,
            uniformSpotLight[i].uniformDirection, uniformSpotLight[i].uniformEdge);
    }
}

void Shader::CompileShader(const char *vertexShaderCode, const char *fragmentShaderCode) {
    
    shaderId = glCreateProgram();
    
    if (!shaderId) {
        printf("Error creating shader program!\n");
        return;
    }
    
    AddShader(shaderId, vertexShaderCode, GL_VERTEX_SHADER);
    AddShader(shaderId, fragmentShaderCode, GL_FRAGMENT_SHADER);
    
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    
    glLinkProgram(shaderId);
    glGetProgramiv(shaderId, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderId, sizeof(eLog), nullptr, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }
    
    glValidateProgram(shaderId);
    glGetProgramiv(shaderId, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderId, sizeof(eLog), nullptr, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }
    
    uniformModel = glGetUniformLocation(shaderId, "model");
    uniformProjection = glGetUniformLocation(shaderId, "projection");
    uniformView = glGetUniformLocation(shaderId, "view");
    uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderId, "directionalLight.base.colour");
    uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderId, "directionalLight.base.ambientIntensity");
    uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderId, "directionalLight.direction");
    uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderId, "directionalLight.base.diffuseIntensity");
    uniformSpecularIntensity = glGetUniformLocation(shaderId, "material.specularIntensity");
    uniformShininess = glGetUniformLocation(shaderId, "material.shininess");
    uniformEyePosition = glGetUniformLocation(shaderId, "eyePosition");
    
    uniformPointLightCount = glGetUniformLocation(shaderId, "pointLightCount");
    uniformSpotLightCount = glGetUniformLocation(shaderId, "spotLightCount");
    
    for(size_t i = 0; i < MAX_POINT_LIGHTS; i++) {
        char locBuff[100] = { '\0' };
        
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.colour", static_cast<int>(i));
        uniformPointLight[i].uniformColour = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", static_cast<int>(i));
        uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", static_cast<int>(i));
        uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", static_cast<int>(i));
        uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", static_cast<int>(i));
        uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", static_cast<int>(i));
        uniformPointLight[i].uniformLinear = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", static_cast<int>(i));
        uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderId, locBuff);
    }
    
    for(size_t i = 0; i < MAX_SPOT_LIGHTS; i++) {
        char locBuff[100] = { '\0' };
        
        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.colour", static_cast<int>(i));
        uniformSpotLight[i].uniformColour = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", static_cast<int>(i));
        uniformSpotLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", static_cast<int>(i));
        uniformSpotLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", static_cast<int>(i));
        uniformSpotLight[i].uniformPosition = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", static_cast<int>(i));
        uniformSpotLight[i].uniformConstant = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", static_cast<int>(i));
        uniformSpotLight[i].uniformLinear = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.exponent", static_cast<int>(i));
        uniformSpotLight[i].uniformExponent = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", static_cast<int>(i));
        uniformSpotLight[i].uniformDirection = glGetUniformLocation(shaderId, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", static_cast<int>(i));
        uniformSpotLight[i].uniformEdge = glGetUniformLocation(shaderId, locBuff);
    }
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);
    
    const GLchar* theCode[1];
    theCode[0] = shaderCode;
    
    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);
    
    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);
    
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
        printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
        return;
    }
    
    glAttachShader(theProgram, theShader);
}
