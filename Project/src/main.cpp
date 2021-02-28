#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = M_PI / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "shaders/shader.vert";

// Fragment Shader
static const char* fShader = "shaders/shader.frag";


void CreateObjects() {
    
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    
    Mesh *obj1 = new Mesh();
    obj1->Create(vertices, indices, 12, 12);
    
    meshList.push_back(obj1);
    
    Mesh *obj2 = new Mesh();
    obj2->Create(vertices, indices, 12, 12);
    
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
    
    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 1.0f);
    
    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
    glm::mat4 projection = glm::perspective(45.0f, static_cast<GLfloat>(mainWindow.GetBufferWidth()) / static_cast<GLfloat>(mainWindow.GetBufferHeight()), 0.1f, 100.0f);
    
    // Loop until window closed
    while(!mainWindow.GetShouldClose()) {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;
        
        // Get + handle user input events
        glfwPollEvents();
        
        camera.KeyControl(mainWindow.GetKeys(), deltaTime);
        
        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].Use();
        
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformView = shaderList[0].GetViewLocation();
        {
            glm::mat4 model(1.0f);

            model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
            
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

            meshList[0]->Render();
            
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
            
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
            
            meshList[1]->Render();
            
        }
        glUseProgram(0);
        
        mainWindow.SwapBuffers();
    }
    
    return 0;
}
