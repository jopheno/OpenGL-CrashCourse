#include "Window.h"

Window::Window(): width(800), height(600) {}
Window::Window(GLint width, GLint height): width(width), height(height) {}

Window::~Window() {
    if (mainWindow) {
        glfwDestroyWindow(mainWindow);
    }
    
    glfwTerminate();
}

bool Window::Initialise() {
    // Initialise GLFW
    if(!glfwInit()) {
        printf("GLFW initialisation failed!\n");
        glfwTerminate();
        
        return false;
    }
    
    // Setup GLFW Window Properties

    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    // Core profile - No Backwards Compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    mainWindow = glfwCreateWindow(width, height, "Test Window", nullptr, nullptr);
    if (!mainWindow){
        printf("GLFW window creation failed!\n");
        glfwTerminate();
        return 1;
    }
    
    // Get Buffer size information
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    
    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);
    
    // Allow modern extension features
    glewExperimental = GL_TRUE;
    
    if (glewInit() != GLEW_OK) {
        printf("GLEW initialisation failed!\n");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }
    
    // Enables depth testing to determinate which triangles are deeper in the image
    glEnable(GL_DEPTH_TEST);
    
    // Setup Viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);
    
    return true;
}
