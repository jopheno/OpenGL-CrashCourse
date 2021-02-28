#include "Light.h"

Light::Light(): colour(1.0f, 1.0f, 1.0f), ambientIntensity(1.0f), direction(0.0f, -1.0f, 0.0f), diffuseIntensity(0.0f) {
    
}

Light::Light(glm::vec3 colour, GLfloat ambientIntensity, glm::vec3 direction, GLfloat diffuseIntensity): colour(colour), ambientIntensity(ambientIntensity), direction(direction), diffuseIntensity(diffuseIntensity) {
    
}

Light::~Light() {}

void Light::Use(GLfloat ambientIntensityLocation, GLfloat colourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation) {
    glUniform3f(colourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}
