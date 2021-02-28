#include "Camera.h"


Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed): position(startPosition), worldUp(startUp), yaw(startYaw), pitch(startPitch), front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(startMoveSpeed), turnSpeed(startTurnSpeed)
{
    Update();
}

void Camera::KeyControl(bool *keys) {
    if (keys[GLFW_KEY_W])
        position += front * movementSpeed;
    if (keys[GLFW_KEY_S])
        position -= front * movementSpeed;
    if (keys[GLFW_KEY_D])
        position += right * movementSpeed;
    if (keys[GLFW_KEY_A])
        position -= right * movementSpeed;
    
    
}

glm::mat4 Camera::CalculateViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::Update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    glm::normalize(front);
    
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
