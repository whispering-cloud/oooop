#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include "usrs.h"



int main() {
    // usrlib
    usrlib->usrlib_init();
    usrlib->keyputh->keyputCall;
    /*
    widget* a = new widget(1, 1, 1, 1, 1);
    spirit* b = new spirit(2, 1, 1, 1, 1, a);
    widget* c = new widget(3, 1, 1, 1, 1, b);
    a->deleteRecursion();
    */
    // openGL init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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