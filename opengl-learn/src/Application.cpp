#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#define GL_SILENCE_DEPRECATION
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#endif

#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#define BUFFER_OFFSET(i) ((char *)NULL (i))
#include <iostream>

void ifMacos(void) {
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    std::cout << "\n Running in MacOS...\n" << std::endl;
#endif
}

static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* msg = (char*)alloca(length * sizeof(char)); \
            glGetShaderInfoLog(id, length, &length, msg);
        std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader Compile Failed!!!" << std::endl;
        std::cout << msg << std::endl;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vShader, const std::string& fShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void preTriangle(void) {
    float positions[6] = {
            -0.5f, -0.5f,
            0.0f, 0.5f,
            0.5f, -0.5f
    };

    // c++ in opengl 3.2 or newer require generate and bind vertex array
    unsigned int vao; // vertex array
    unsigned int vbo; // vertex buffer

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // Shaders
    std::string vShader =
        "#version 410 core\n"
        "\n"
        "layout (location = 0) in vec4 position;"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

    std::string fShader =
        "#version 410 core\n"
        "\n"
        "layout (location = 0) out vec4 color;"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(0.0, 1.0, 0.0, 1.0);\n"
        "}\n";

    unsigned int shader = CreateShader(vShader, fShader);
    glUseProgram(shader);
}

void initWindow(void) {
    preTriangle();
}

void render(void) {
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}


int main(int argc, char** argv) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    ifMacos();

    // create window
    GLFWwindow* window;
    window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }

    std::cout << "\nCurrent OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    // prepare for rendering
    initWindow();

    // running window
    while (!glfwWindowShouldClose(window)) {
        render();
        glfwSwapInterval(1); //Vsync
        // swap front and back buffers
        glfwSwapBuffers(window); //Vsync
        // Poll for and process events
        glfwPollEvents();
    }

    // program finish
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
