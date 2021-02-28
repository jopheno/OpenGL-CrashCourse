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
    
    bool* GetKeys() { return keys; }
    GLfloat GetChangeInXAxis();
    GLfloat GetChangeInYAxis();
    
private:
    GLFWwindow *mainWindow;
    
    GLint width, height;
    GLint bufferWidth, bufferHeight;
    
    bool keys[1024];
    
    GLfloat lastX;
    GLfloat lastY;

    GLfloat xChange;
    GLfloat yChange;
    
    bool mouseFirstMoved;

    void createCallbacks();
    static void handleKeys(GLFWwindow* specificWindow, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* specificWindow, double xPos, double yPos);
};
