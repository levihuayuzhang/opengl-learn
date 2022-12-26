// ingnore xcode documentation warnings
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
// ingnore deprecation warning
#define GL_SILENCE_DEPRECATION
// multi-header warning for macos sdl2
#ifdef __APPLE__
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#define BUFFER_OFFSET(i) ((char *)NULL (i))
#include <iostream>

void init(GLFWwindow *window){
    
}

void display(GLFWwindow *window, double currentTime){
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv) {
    glewExperimental = GL_TRUE;
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    // force using newer version of OpenGL in MacOS
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // highest for MacOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    
    // create window
    GLFWwindow *window;
    window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    // set render resolution for Retina display
    // (make sure content rendered into frame buffer is fit with content displayed
    // in GLFW window)
    int actualScreenWidth, actualScreenHeight;
    // retrieve actual resolution from frame buffer
    glfwGetFramebufferSize(window, &actualScreenWidth, &actualScreenHeight);
    glViewport(0,0,actualScreenWidth,actualScreenHeight);
    
    if (glewInit() != GLEW_OK){
        exit(EXIT_FAILURE);
    }
    
    glfwSwapInterval(1); //Vsync
    
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    init(window);
    
    while (!glfwWindowShouldClose(window)) {
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        display(window, glfwGetTime());
        glfwSwapBuffers(window); //Vsync
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
