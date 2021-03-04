#pragma once
#include "Light.h"

class PointLight : public Light {
public:
    PointLight();
    PointLight(glm::vec3 colour, GLfloat ambientIntensity, GLfloat diffuseIntensity, glm::vec3 position, GLfloat constant, GLfloat linear, GLfloat expoent);
    ~PointLight();
    
    void Use(GLfloat ambientIntensityLocation, GLfloat colourLocation, GLfloat diffuseIntensityLocation,
             GLfloat positionLocation, GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation);
    
private:
    glm::vec3 position;
    
    // ax^2 + bx + c
    GLfloat constant, linear, exponent;
};
