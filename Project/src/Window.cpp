#include "Window.h"

Window::Window(): width(800), height(600) {
    for (size_t i = 0; i < 1024; i++) {
        keys[i] = false;
    }
    
    mouseFirstMoved = true;
}
Window::Window(GLint width, GLint height): width(width), height(height) {
    for (size_t i = 0; i < 1024; i++) {
        keys[i] = false;
    }
    
    mouseFirstMoved = true;
}

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
    
    // Handle Key + Mouse Input
    createCallbacks();
    
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
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
    
    glfwSetWindowUserPointer(mainWindow, this);
    
    return true;
}

void Window::createCallbacks() {
    glfwSetKeyCallback(mainWindow, &Window::handleKeys);
    glfwSetCursorPosCallback(mainWindow, &Window::handleMouse);
}

void Window::handleKeys(GLFWwindow* specificWindow, int key, int code, int action, int mode) {
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(specificWindow));
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(specificWindow, GLFW_TRUE);
    }
    
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            window->keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            window->keys[key] = false;
        }
    }
}

void Window::handleMouse(GLFWwindow *specificWindow, double xPos, double yPos) {
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(specificWindow));
    
    if (window->mouseFirstMoved) {
        window->lastX = xPos;
        window->lastY = yPos;
        window->mouseFirstMoved = false;
    }
    
    window->xChange = xPos - window->lastX;
    window->yChange = window->lastY - yPos;
    
    window->lastX = xPos;
    window->lastY = yPos;
}

GLfloat Window::GetChangeInXAxis() {
    GLfloat change = xChange;
    xChange = 0.0f;

    return change;
}

GLfloat Window::GetChangeInYAxis() {
    GLfloat change = yChange;
    yChange = 0.0f;

    return change;
}
