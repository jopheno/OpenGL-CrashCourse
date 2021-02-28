#include "Light.h"

Light::Light(): colour(1.0f, 1.0f, 1.0f), ambientIntensity(1.0f) {
    
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity): colour(red, green, blue), ambientIntensity(ambientIntensity) {
    
}

Light::~Light() {}

void Light::Use(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation) {
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
}
