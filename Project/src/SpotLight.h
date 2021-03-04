#pragma once

#include "PointLight.h"

class SpotLight : public PointLight {
public:
    SpotLight();
    SpotLight(glm::vec3 colour, GLfloat ambientIntensity, GLfloat diffuseIntensity, glm::vec3 position, GLfloat constant, GLfloat linear, GLfloat exponent, glm::vec3 direction, GLfloat edge);
    ~SpotLight();
    
    void Use(GLuint ambientIntensityLocation, GLuint colourLocation, GLuint diffuseIntensityLocation,
             GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint directionLocation, GLuint edgeLocation);
    
    void SetFlash(glm::vec3 pos, glm::vec3 dir);
    
private:
    glm::vec3 direction;
    
    GLfloat edge, procEdge;
};
