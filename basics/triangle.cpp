#include <iostream>
#include <GLFW/glfw3.h>
#include <math.h>


int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cout << "Init error";
        return -1;
    }

    window = glfwCreateWindow(800, 600, "Hello", 0, 0);
    if (!window) {
        std::cout << "Window creation error";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    float xPos = 0; float yPos = 0; float radius = 1.0f;
    bool toggle = false;

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0, 1.0, 1.0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(0, 0.5f, 0);
        // give vertex of cordinates
        glVertex3f(-0.6f, -0.4f, 0.0f);
        // interpolate some different colors 
        glColor3f(1.0f, 0.5f, 0);
        glVertex3f(0.6f, -0.4f, 0.0f);
        glColor3f(0, 0.5f, 1.0);
        glVertex3f(0.f, 0.6f, 0.0f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}