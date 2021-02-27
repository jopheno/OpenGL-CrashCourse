#pragma once

#include <GL/glew.h>

class Mesh {
public:
    Mesh();
    ~Mesh();
    
    void Create(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void Render();
    void Clear();
    
private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
    
    friend int main(int argc, char** argv);
};
