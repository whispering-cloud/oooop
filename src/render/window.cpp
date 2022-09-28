#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../usrs.h"

unsigned int VBO, VAO;
shader* abc;
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
        abc->setUniform("ourColor", sin(glfwGetTime())/2.0f+0.5f, 1-(sin(glfwGetTime()) / 2.0f + 0.5f), 0.5f, 1.0f);
        // render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        
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

    // shader generate
    shader tst("./src/render/renderer_glsl/test_vertex.glsl", "./src/render/renderer_glsl/test_frag.glsl");
    abc = &tst;

    // test triangle
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    // texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    // stay
    loopRender();
    // destroy
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();

    return 1;
}



