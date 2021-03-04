#pragma once
#include "Light.h"

class PointLight : public Light {
public:
    PointLight();
    PointLight(glm::vec3 colour, GLfloat ambientIntensity, GLfloat diffuseIntensity, glm::vec3 position, GLfloat constant, GLfloat linear, GLfloat expoent);
    ~PointLight();
    
    void Use(GLuint ambientIntensityLocation, GLuint colourLocation, GLuint diffuseIntensityLocation,
             GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);
    
protected:
    glm::vec3 position;
    
    // ax^2 + bx + c
    GLfloat constant, linear, exponent;
};
