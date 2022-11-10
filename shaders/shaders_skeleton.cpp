#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// vertex shader source

const char* vertex120 = R"END(
#version 120
attribute vec3 inPosition;
attribute vec3 inColor;
varying vec3 outColor;
void main()
{
    outColor = inColor;
    gl_Position = vec4(inPosition,1);
}
)END";

// fragment shader source

const char* raster120 = R"END(
#version 120
varying vec3 outColor;
void main()
{
    gl_FragColor = vec4(outColor,1);
}
)END";

int main()

{
    GLFWwindow* window;
    if (!glfwInit())
    {
        std::cout << "eroor";
        exit(-1);
    }
    // initial skeleton
    window = glfwCreateWindow(800, 800, "Hello", 0, 0);
    if (!window) {
        std::cout << "window creation error";
        glfwTerminate();
        return -1;
    }
    // context creation
    glfwMakeContextCurrent(window);

    //init vertex shader
    GLuint vertexshader =  glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader, 1, &vertex120, 0);
    glCompileShader(vertexshader);

    GLint compilationstatus;
    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &compilationstatus);
    if (compilationstatus == GL_FALSE)
    {
        char message[258];
        glGetShaderInfoLog(vertexshader, sizeof(message), 0, &message[0]);
        std::cout << message;
        exit(1);

    }

    //init fragment shader
    GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader, 1, &vertex120, 0);
    glCompileShader(fragmentshader);

    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &compilationstatus);
    if (compilationstatus == GL_FALSE)
    {
        char message[258];
        glGetShaderInfoLog(fragmentshader, sizeof(message), 0, &message[0]);
        std::cout << message;
        exit(1);

    }

    // create or init shared program
    GLuint sharedprogram = glCreateProgram();
    glAttachShader(sharedprogram, vertexshader);
    glAttachShader(sharedprogram, fragmentshader);
    glLinkProgram(sharedprogram);
    glCompileShader(fragmentshader);

    glGetShaderiv(sharedprogram, GL_COMPILE_STATUS, &compilationstatus);
    if (compilationstatus == GL_FALSE)
    {
        char message[258];
        glGetShaderInfoLog(sharedprogram, sizeof(message), 0, &message[0]);
        std::cout << message;
        exit(1);

    }


    // render loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0, 1.0, 0.0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwTerminate();
}