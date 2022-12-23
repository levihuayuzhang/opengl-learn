// ingnore xcode documentation warnings
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#define GLFW_INCLUDE_GLCOREARB
//ingnore deprecation warning
#define GL_SILENCE_DEPRECATION
#include "GLFW/glfw3.h"

#define BUFFER_OFFSET(i) ((char *)NULL (i))

int main(int argc, char** argv) {
    GLFWwindow *window;
    
    if (!glfwInit()) {
        return -1;
    }
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    
    window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
        glfwMakeContextCurrent(window);
        
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        
        glfwTerminate();
        return 0;
}
