#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light {
public:
    Light();
    Light(glm::vec3 colour, GLfloat ambientIntensity, glm::vec3 direction, GLfloat diffuseIntensity );
    ~Light();
    
    void Use(GLfloat ambientIntensityLocation, GLfloat colourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);
    
    
private:
    glm::vec3 colour;
    GLfloat ambientIntensity;
    
    glm::vec3 direction;
    GLfloat diffuseIntensity;
};
