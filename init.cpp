#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>


#include <algorithm>
#include "usrs.h"


int main() {
    
    // openGL init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // irrklang
    usrlib->soundEngine = irrklang::createIrrKlangDevice();
    
    // usrlib
    usrlib->usrlib_init();
    
    usrlib->windowh->setSize(MAX_WIDTH, MAX_HEIGHT);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    if (usrlib->windowh->genWindow() == -1) {
        std::cout << "window generate error\n";
    }
	//std::cout << 1;
    
    delete usrlib;
    usrlib = nullptr;
	return 0;
}