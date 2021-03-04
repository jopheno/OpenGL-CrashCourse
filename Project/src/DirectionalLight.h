#pragma once
#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight();
    DirectionalLight(glm::vec3 colour, GLfloat ambientIntensity, GLfloat diffuseIntensity, glm::vec3 direction );
    ~DirectionalLight();
    
    void Use(GLuint ambientIntensityLocation, GLuint colourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation);
    
private:
    glm::vec3 direction;
};
