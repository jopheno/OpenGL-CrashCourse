#include "Texture.h"

Texture::Texture(): textureId(0), width(0), height(0), bitDepth(0), fileLocation(nullptr) {}

Texture::Texture(char* fileLocation): Texture::Texture() {
    this->fileLocation = fileLocation;
}

bool Texture::LoadWithAlpha() {
    if (fileLocation == nullptr) {
        printf("Failed to load image, any file location was given!\n");
        return false;
    }

    unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
    
    if (!texData) {
        printf("Failed to load image: %s\n", fileLocation);
        return false;
    }
    
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    stbi_image_free(texData);
    
    return true;
}

bool Texture::Load() {
    if (fileLocation == nullptr) {
        printf("Failed to load image, any file location was given!\n");
        return false;
    }

    unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
    
    if (!texData) {
        printf("Failed to load image: %s\n", fileLocation);
        return false;
    }
    
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    stbi_image_free(texData);
    
    return true;
}

void Texture::Use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::Clear() {
    glDeleteTextures(1, &textureId);
    textureId = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = nullptr;
}

Texture::~Texture() {
    Clear();
}
