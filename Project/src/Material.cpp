#include "Material.h"

Material::Material(): specularIntensity(0.0f), shininess(0.0f) {
    
}

Material::Material(GLfloat specularIntensity, GLfloat shineFactor): specularIntensity(specularIntensity), shininess(shineFactor) {
    
}

Material::~Material() {}

void Material::Use(GLuint specularIntensityLocation, GLuint shininessLocation) {
    glUniform1f(specularIntensityLocation, specularIntensity);
    glUniform1f(shininessLocation, shininess);
}
