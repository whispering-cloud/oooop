#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "..\..\include\render\window.h"

void window::loopRender()
{
    while (!glfwWindowShouldClose(usrlib->wds))
    {
        // process key control
        
        // flash window
        glfwSwapBuffers(usrlib->wds);
        glfwPollEvents();
    }
}

int window::genWindow()
{
    usrlib->wds = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (usrlib->wds == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(usrlib->wds);
    // glad
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //compat forward for max os x
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    // stay
    loopRender();
    // destroy
    glfwTerminate();

    return 1;
}


