#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "../../usrs.h"

vabo tria;
//unsigned int VBO, VAO;


void window::loopRender()
{
    while (!glfwWindowShouldClose(usrlib->wds))
    {
        // render test triangle
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //abc->enable();
        //usrlib->glslPrograms[0].setUniform("ourColor", sin(glfwGetTime())/2.0f+0.5f, 1-(sin(glfwGetTime()) / 2.0f + 0.5f), 0.5f, 1.0f);
        // render the triangle
        tria.render();

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    usrlib->windowh->setSize(width, height);
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
    glfwSetFramebufferSizeCallback(usrlib->wds, framebuffer_size_callback);

    rootRender = new widget(0, 0, 0, 0, 0);


    // tst
    
    // shader generate
    usrlib->glslPrograms.push_back(shader("./src/render/renderer_glsl/test_vertex.glsl", "./src/render/renderer_glsl/test_frag.glsl"));

    // test triangle
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };
    tria = vabo(vertices, sizeof(vertices), 3, &usrlib->glslPrograms[0], GL_DYNAMIC_DRAW, GL_TRIANGLES, 2);

    // texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    // tst end





    // stay
    loopRender();
    // destroy
    glfwTerminate();
    for (re i = 0; i < delvao.size(); i++) {
        glDeleteVertexArrays(1, &delvao[i]);
    }
    for (re i = 0; i < delvbo.size(); i++) {
        glDeleteBuffers(1, &delvbo[i]);
    }
    for (re i = 0; i < usrlib->glslPrograms.size(); i++) {
        glDeleteProgram(usrlib->glslPrograms[i]);
    }
    rootRender->deleteRecursion();
    return 1;
}



