#include "Shader.h"

Shader::Shader(): shaderId(0), uniformProjection(0), uniformModel(0), uniformView(0) {}

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
    return uniformColour;
}

GLuint Shader::GetAmbientIntensityLocation() {
    return uniformAmbientIntensity;
}

GLuint Shader::GetDiffuseIntensityLocation() {
    return uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation() {
    return uniformDirection;
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
    uniformColour = glGetUniformLocation(shaderId, "directionalLight.colour");
    uniformAmbientIntensity = glGetUniformLocation(shaderId, "directionalLight.ambientIntensity");
    uniformDirection = glGetUniformLocation(shaderId, "directionalLight.direction");
    uniformDiffuseIntensity = glGetUniformLocation(shaderId, "directionalLight.diffuseIntensity");
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
