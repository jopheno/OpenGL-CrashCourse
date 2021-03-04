#include "PointLight.h"

PointLight::PointLight(): Light(), position(0.0f, 0.0f, 0.0f), constant(1.0f), linear(0.0f), exponent(0.0f) {};

PointLight::PointLight(glm::vec3 colour, GLfloat ambientIntensity, GLfloat diffuseIntensity, glm::vec3 position, GLfloat constant, GLfloat linear, GLfloat exponent): Light(colour, ambientIntensity, diffuseIntensity), position(position), constant(constant), linear(linear), exponent(exponent) {
    
}

void PointLight::Use(GLuint ambientIntensityLocation, GLuint colourLocation, GLuint diffuseIntensityLocation,
                     GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation) {
    Light::Use(ambientIntensityLocation, colourLocation, diffuseIntensityLocation);
    
    glUniform3f(positionLocation, position.x, position.y, position.z);
    glUniform1f(constantLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(exponentLocation, exponent);
}

PointLight::~PointLight() {}
