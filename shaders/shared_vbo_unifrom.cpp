#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


GLfloat vertices[] = {
        -1, -1, 0,
        -1,  1, 0,
         1, -1, 0,
         1, -1, 0,
        -1,  1, 0,
         1,  1, 0
};

GLfloat colors[] = {
    1, 0, 0,
    0, 1, 0,
    0, 0, 1,
    1, 1, 0,
    1, 0, 1,
    0, 1, 1
};


// vertex shader source

const char* vertex120 = R"END(
#version 120
attribute vec3 inPosition;
attribute vec3 inColor;
unifrom mat4 matrix;
varying vec3 outColor;
void main()
{
    outColor = inColor;
    gl_Position = inposition * matrix;
}
)END";

// fragment shader source

const char* raster120 = R"END(
#version 120
varying vec3 outColor;
void main()
{
    gl_FragColor = outcolor ; 
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

    // vbo setup

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    GLuint colorsbuffer;
    glGenBuffers(1, &colorsbuffer);

    //send data to GPU
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorsbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // create or init attribute position (a_pos)
    GLuint attributeposition = glGetAttribLocation(sharedprogram, "inPosition");
    glEnableVertexAttribArray(attributeposition);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(attributeposition, 3, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint attributecolor = glGetAttribLocation(sharedprogram, "inPosition");
    glEnableVertexAttribArray(attributecolor);
    glBindBuffer(GL_ARRAY_BUFFER, colorsbuffer);
    glVertexAttribPointer(attributecolor, 3, GL_FLOAT, GL_FALSE, 0, 0);


    // uniform

    GLuint attribmatrix = glGetUniformLocation(sharedprogram, "matrix");
    float alpha = 0;


    // render loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0, 1.0, 0.0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        float sa = 0.5 * sin(alpha);
        float ca = 0.5 * cos(alpha);

        alpha += 0.1;

        GLfloat matrix[] = {
                            sa, -ca, 0, 0,
                            ca, sa, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1
                            };
        glUniformMatrix4fv(attribmatrix, 1, GL_FALSE, matrix);

        glDrawArrays(GL_TRIANGLES, 0, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwTerminate();
}