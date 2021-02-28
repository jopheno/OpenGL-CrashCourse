#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light {
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity);
    ~Light();
    
    void Use(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation);
    
    
private:
    glm::vec3 colour;
    GLfloat ambientIntensity;
};
