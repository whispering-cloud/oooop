#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "../../usrs.h"
vabo tria;
//unsigned int VBO, VAO;

void window::renderRecursion(widget* x) {
    if (x == nullptr) return;
    x->update();
    for (re i = 0; i < x->children.size(); i++) {
        renderRecursion(x->children[i]);
    }
}

void window::loopRender()
{
    while (!glfwWindowShouldClose(usrlib->wds))
    {
        // enable framebuffer
        if (FRAMEBUFFER_ENABLE) {
            glBindFramebuffer(GL_FRAMEBUFFER, usrlib->fbo);
            //glEnable(GL_DEPTH_TEST);
        }
        

        // render test triangle
        // render
        // ------
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //abc->enable();
        //usrlib->glslPrograms[0].setUniform("ourColor", sin(glfwGetTime())/2.0f+0.5f, 1-(sin(glfwGetTime()) / 2.0f + 0.5f), 0.5f, 1.0f);
        // render the triangle
        //tria.render();
        renderRecursion(rootRender);
        // process key control
        usrlib->keyputh->detectKey(usrlib->wds);
        // Ticking
        usrlib->ticking();
        // flash window
        glfwSwapBuffers(usrlib->wds);
        glfwPollEvents();
        if (FRAMEBUFFER_ENABLE) {
            // render framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            //glDisable(GL_DEPTH_TEST);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            usrlib->glslPrograms[0].enable();
            frameCanvas->update();
        }
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

void bark(point clickPosition) {
    widget* ths = usrlib->windowh->rootRender->children[0]->children[0];
    ths->relocate(clickPosition, clickPosition + ths->getSize());
    std::cout << "DO NOT TOUCH ME" << std::endl;
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
    
    // vsync
    glfwSwapInterval(1);
    
    // mixer
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(usrlib->wds, framebuffer_size_callback);
    
    // shader generate
    usrlib->glslPrograms.push_back(shader("./src/render/renderer_glsl/test_vertex.glsl", "./src/render/renderer_glsl/test_frag.glsl"));
    usrlib->glslPrograms.push_back(shader("./src/render/renderer_glsl/font_vertex.glsl", "./src/render/renderer_glsl/font_frag.glsl"));
    
    // texture generate
    textureList.push_back(texture("./resource/wall.jpg")); // id1
    textureList.push_back(texture("./resource/mope.png")); 
    // font init
    glm::mat4 orth = glm::ortho(0.0f, static_cast<GLfloat>(MAX_WIDTH), 0.0f, static_cast<GLfloat>(MAX_HEIGHT));
    usrlib->glslPrograms[1].enable();
    usrlib->glslPrograms[1].setUniform("projection", glm::value_ptr(orth));
    texture::loadFont();

    // frame buffer init
    if (FRAMEBUFFER_ENABLE) {
        glGenFramebuffers(1, &usrlib->fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, usrlib->fbo);
        
        glGenTextures(1, &usrlib->frameTexture);
        glBindTexture(GL_TEXTURE_2D, usrlib->frameTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, MAX_WIDTH, MAX_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, usrlib->frameTexture, 0);

        glGenRenderbuffers(1, &usrlib->rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, usrlib->rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, MAX_WIDTH, MAX_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, usrlib->rbo); // now actually attach it
        
                                                                                                              // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            logError(1);// ERROR::FRAMEBUFFER:: Framebuffer is not complete!
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    


    // tree renderer init
    rootRender = new widget(0, 0, 0, 0, 0);
    if (FRAMEBUFFER_ENABLE) {
        frameCanvas = new spirit(-1, 0, 0, MAX_WIDTH, MAX_HEIGHT, 0, false, usrlib->frameTexture);
        frameCanvas->enable(true);
    }
    // tst
    widget* axx = new widget(1, 0, 0, 0, 0, rootRender);
    button* bxx = new button(2, 100, 100, 200, 200, axx, false, bark);
    spirit* dxx = new spirit(4, 0, 0, bxx->getSize().x, bxx->getSize().y, bxx, true, textureList[1]);
    text* cxx = new text(3, 100, 100, 1, bxx, true, "1234");
    cxx->setColor({ 0, 0, 1 }).setScale(1.0f);
    bxx->enable(true);
    cxx->enable(true);
    dxx->enable(true);
    //std::cout << textureList[0].index;
    //text* dxx = new text(4, 500, 0, 1, cxx, true, "123");
    //dxx->setColor(glm::vec3(0.3f, 0.5f, 0.7f)).setScale(0.7f).setText("hello world").updateRender();
    /*
    // test triangle
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };
    tria = vabo(vertices, sizeof(vertices), 3, &usrlib->glslPrograms[0], GL_DYNAMIC_DRAW, GL_TRIANGLES, 2);
    */
    
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



