#include <GLFW/glfw3.h>
#include <iostream>
#include "drawing/GLDRAWER.h"

int main(void)
{
    std::cout << "starting!" << std::endl;
    GLFWwindow* window;

    std::cout << "attempting glfwInit!" << std::endl;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    std::cout << "attempting window creation!" << std::endl;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "GLFW CMake starter", NULL, NULL);
    if (!window)
    {
        std::cout << "failed! going to glfwTerminate" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glClearColor( 0.4f, 0.3f, 0.4f, 0.0f );

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
