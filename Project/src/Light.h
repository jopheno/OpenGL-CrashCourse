#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light {
public:
    Light();
    Light(glm::vec3 colour, GLfloat ambientIntensity, GLfloat diffuseIntensity );
    ~Light();
    
    void Use(GLuint ambientIntensityLocation, GLuint colourLocation, GLuint diffuseIntensityLocation);
    
    
protected:
    glm::vec3 colour;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;
};
