#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../usrs.h"

void window::loopRender()
{
    while (!glfwWindowShouldClose(usrlib->wds))
    {
        // process key control
        usrlib->keyputh->detectKey(usrlib->wds);
        // Ticking
        usrlib->ticking();
        // flash window
        glfwSwapBuffers(usrlib->wds);
        glfwPollEvents();
    }
    return;
}

void window::setSize(int x, int y) {
    width = x;
    height = y;
    return;
}

int window::genWindow()
{
    usrlib->wds = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
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
    glViewport(0, 0, width, height);
    // stay
    loopRender();
    // destroy
    glfwTerminate();

    return 1;
}


