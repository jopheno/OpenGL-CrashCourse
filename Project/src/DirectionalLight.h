#pragma once
#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight();
    DirectionalLight(glm::vec3 colour, GLfloat ambientIntensity, GLfloat diffuseIntensity, glm::vec3 direction );
    ~DirectionalLight();
    
    void Use(GLfloat ambientIntensityLocation, GLfloat colourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);
    
private:
    glm::vec3 direction;
};
