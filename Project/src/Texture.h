#pragma once

#include <GL/glew.h>

#include "stb_image.h"

class Texture {
public:
    Texture();
    Texture(const char* fileLocation);
    ~Texture();
    
    bool Load();
    bool LoadWithAlpha();
    void Use();
    void Clear();
private:
    GLuint textureId;
    int width, height, bitDepth;
    
    const char* fileLocation;
};
