#include <iostream>
#include <GLFW/glfw3.h>

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