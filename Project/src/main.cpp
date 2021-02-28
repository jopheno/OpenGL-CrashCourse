#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = M_PI / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

Texture brickTexture;
Texture dirtTexture;

Light mainLight;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "shaders/shader.vert";

// Fragment Shader
static const char* fShader = "shaders/shader.frag";

void calcAverageNormals(unsigned int* indices, unsigned int indicesCount, GLfloat* vertices, unsigned int verticesCount,
    unsigned int vertexLength, unsigned int vertexNormalsOffset) {
    
    for (size_t i = 0; i < indicesCount; i += 3) {
        unsigned int in0 = indices[i] * vertexLength;
        unsigned int in1 = indices[i+1] * vertexLength;
        unsigned int in2 = indices[i+2] * vertexLength;
        
        
        glm::vec3 v1 (
            vertices[in1] - vertices[in0],
            vertices[in1+1] - vertices[in0+1],
            vertices[in1+2] - vertices[in0+2]
        );
        
        glm::vec3 v2 (
            vertices[in2] - vertices[in0],
            vertices[in2+1] - vertices[in0+1],
            vertices[in2+2] - vertices[in0+2]
        );
        
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);
        
        in0 += vertexNormalsOffset; in1 += vertexNormalsOffset; in2 += vertexNormalsOffset;
        
        vertices[in0] += normal.x;
        vertices[in0+1] += normal.y;
        vertices[in0+2] += normal.z;
        
        vertices[in1] += normal.x;
        vertices[in1+1] += normal.y;
        vertices[in1+2] += normal.z;
        
        vertices[in2] += normal.x;
        vertices[in2+1] += normal.y;
        vertices[in2+2] += normal.z;
    }
    
    for (size_t i = 0; i < verticesCount/vertexLength; i++) {
        unsigned int nOffset = i * vertexLength + vertexNormalsOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset+1], vertices[nOffset+2]);
        vec = glm::normalize(vec);

        vertices[nOffset] = vec.x; vertices[nOffset+1] = vec.y; vertices[nOffset+2] = vec.z;
    }
    
}

void CreateObjects() {
    
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
    //    X      Y     Z      U     V            Normals
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f,   0.5f, 0.0f,     0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,   1.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,    0.5f, 1.0f,     0.0f, 0.0f, 0.0f
    };
    
    calcAverageNormals(indices, 12, vertices, 32, 8, 5);
    
    Mesh *obj1 = new Mesh();
    obj1->Create(vertices, indices, 32, 12);
    
    meshList.push_back(obj1);
    
    Mesh *obj2 = new Mesh();
    obj2->Create(vertices, indices, 32, 12);
    
    meshList.push_back(obj2);
}

void CreateShaders() {
    Shader *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

int main(int argc, char** argv) {
    
    Window mainWindow(WIDTH, HEIGHT);
    if (!mainWindow.Initialise()) {
        printf("Failed to create window!\n");
        return 1;
    }
    
    CreateObjects();
    
    // Vertex array must be bind for the program to be successfully validated
    glBindVertexArray(meshList[0]->VAO);
    {
        CreateShaders();
    }
    glBindVertexArray(0);
    
    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);
    
    brickTexture = Texture("textures/brick.png");
    dirtTexture = Texture("textures/dirt.png");
    
    brickTexture.Load();
    dirtTexture.Load();
    
    mainLight = Light(glm::vec3(1.0f, 1.0f, 1.0f), 0.3f, glm::vec3(2.0f, -1.0f, -2.0f), 1.0f);
    
    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
    GLuint uniformAmbientIntensity = 0, uniformColour = 0, uniformDiffuseIntensity = 0, uniformDirection = 0;
    glm::mat4 projection = glm::perspective(45.0f, static_cast<GLfloat>(mainWindow.GetBufferWidth()) / static_cast<GLfloat>(mainWindow.GetBufferHeight()), 0.1f, 100.0f);
    
    // Loop until window closed
    while(!mainWindow.GetShouldClose()) {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;
        
        // Get + handle user input events
        glfwPollEvents();
        
        camera.KeyControl(mainWindow.GetKeys(), deltaTime);
        camera.MouseControl(mainWindow.GetChangeInXAxis(), mainWindow.GetChangeInYAxis());
        
        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].Use();
        
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformView = shaderList[0].GetViewLocation();
        uniformColour = shaderList[0].GetColourLocation();
        uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
        uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensityLocation();
        uniformDirection = shaderList[0].GetDirectionLocation();
        
        mainLight.Use(uniformAmbientIntensity, uniformColour, uniformDiffuseIntensity, uniformDirection);

        {
            glm::mat4 model(1.0f);

            model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
            
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

            brickTexture.Use();
            meshList[0]->Render();
            
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
            
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

            dirtTexture.Use();
            meshList[1]->Render();
            
        }
        glUseProgram(0);
        
        mainWindow.SwapBuffers();
    }
    
    return 0;
}
