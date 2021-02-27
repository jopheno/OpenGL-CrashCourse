#pragma once

#include <cstdio>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window();
    Window(GLint width, GLint height);
    ~Window();
    
    bool Initialise();
    GLint GetBufferWidth() { return bufferWidth; }
    GLint GetBufferHeight() { return bufferHeight; }
    
    bool GetShouldClose() { return glfwWindowShouldClose(mainWindow); }
    void SwapBuffers() { glfwSwapBuffers(mainWindow); }
    
private:
    GLFWwindow *mainWindow;
    
    GLint width, height;
    GLint bufferWidth, bufferHeight;
};
