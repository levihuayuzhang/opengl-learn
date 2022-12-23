// ingnore xcode documentation warnings
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
//ingnore deprecation warning
#define GL_SILENCE_DEPRECATION

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>


#define BUFFER_OFFSET(i) ((char *)NULL (i))

int main(int argc, char** argv) {
    GLFWwindow *window;
    
    glewExperimental = GL_TRUE;
    
    if (!glfwInit()) {
        return -1;
    }
    
    // force using newer version of OpenGL in MacOS
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    
    // create window
    window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
    
    // set render resolution for Retina display
    // (make sure content rendered into frame buffer is fit with content displayed
    // in GLFW window)
    int actualScreenWidth, actualScreenHeight;
    // retrieve actual resolution from frame buffer
    glfwGetFramebufferSize(window, &actualScreenWidth, &actualScreenHeight);
    
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glViewport(0,0,actualScreenWidth,actualScreenHeight);
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
