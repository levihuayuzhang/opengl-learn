#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#define BUFFER_OFFSET(i) ((char *)NULL (i))
#include <iostream>


int main(int argc, char** argv) {
    glewExperimental = GL_TRUE;
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    
    // create window
    GLFWwindow *window;
    window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK){
        exit(EXIT_FAILURE);
    }

    
    while (!glfwWindowShouldClose(window)) {



        glfwSwapInterval(1); //Vsync
        glfwSwapBuffers(window); //Vsync
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
