#include "Light.h"

Light::Light(): colour(1.0f, 1.0f, 1.0f), ambientIntensity(1.0f), diffuseIntensity(0.0f) {
    
}

Light::Light(glm::vec3 colour, GLfloat ambientIntensity, GLfloat diffuseIntensity): colour(colour), ambientIntensity(ambientIntensity), diffuseIntensity(diffuseIntensity) {
    
}

Light::~Light() {}

void Light::Use(GLuint ambientIntensityLocation, GLuint colourLocation, GLuint diffuseIntensityLocation) {
    glUniform3f(colourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}
