#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(): Light(), direction(0.0f, -1.0f, 0.0f) {
    
}

DirectionalLight::DirectionalLight(glm::vec3 colour, GLfloat ambientIntensity, GLfloat diffuseIntensity, glm::vec3 direction): Light(colour, ambientIntensity, diffuseIntensity), direction(direction) {
    
}

DirectionalLight::~DirectionalLight() {}

void DirectionalLight::Use(GLuint ambientIntensityLocation, GLuint colourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation) {
    Light::Use(ambientIntensityLocation, colourLocation, diffuseIntensityLocation);

    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}
