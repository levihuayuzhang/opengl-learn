#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#define GL_SILENCE_DEPRECATION
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#endif

#define GLEW_STATIC
#include <GL/glew.h>
// #define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#define BUFFER_OFFSET(i) ((char *)NULL (i))
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

void ifMacos(void) {
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    std::cout <<  "Running in MacOS..." << std::endl;
#endif
}

static ShaderProgramSource ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                // set mode to vertex
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                // set mode to fragment
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str() };
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
        std::cout << (type == GL_VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER) <<  "Shader Compile Failed!!!" << std::endl;
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

//    glDeleteShader(vs);
//    glDeleteShader(fs);
//    glDeleteProgram();

    return program;
}

void preSquare(void) {
    float positions[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
//            0.5f, 0.5f,
            -0.5f, 0.5f
//            -0.5f, -0.5f
    };

    // for index shader (saving memory)
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    // c++ in opengl 3.2 or newer require generate and bind vertex array (core profile on Mac)
    // vertex array
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vertex buffer
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // index shader (for saving memory) (reuse of vertex)
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);
}

void initWindow(void) {
//    preTriangle();
    preSquare();
}

void render(void) {
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // draw index shader
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}


int main(int argc, char** argv) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    ifMacos();

    // create window
    GLFWwindow* window;
    window = glfwCreateWindow(600, 600, "OpenGL Learn", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }

    std::cout << "Current OpenGL version:"  << glGetString(GL_VERSION) << std::endl;

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
