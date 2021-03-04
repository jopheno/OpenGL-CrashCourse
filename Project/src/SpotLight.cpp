#include "SpotLight.h"

SpotLight::SpotLight(): PointLight(), direction(0.0f, -1.0f, 0.0f), edge(0.0f) {
    procEdge = cosf(glm::radians(edge));
}

SpotLight::SpotLight(glm::vec3 colour, GLfloat ambientIntensity, GLfloat diffuseIntensity, glm::vec3 position, GLfloat constant, GLfloat linear, GLfloat exponent, glm::vec3 direction, GLfloat edge): PointLight(colour, ambientIntensity, diffuseIntensity, position, constant, linear, exponent), direction(glm::normalize(direction)), edge(edge) {
    
    procEdge = cosf(glm::radians(edge));
}

SpotLight::~SpotLight() {}

void SpotLight::Use(GLuint ambientIntensityLocation, GLuint colourLocation, GLuint diffuseIntensityLocation,
                    GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint directionLocation, GLuint edgeLocation) {
    
    PointLight::Use(ambientIntensity, colourLocation, diffuseIntensityLocation, positionLocation, constantLocation, linearLocation, exponentLocation);
    
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(edgeLocation, procEdge);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir) {
    position = pos;
    direction = dir;
}
