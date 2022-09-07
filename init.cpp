#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include "usrs.h"


int main() {
    // usrlib
    usrlib = new usrs();
    usrlib->usrlib_init();
    // openGL init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    usrlib->windowh->setSize(1296, 800);
    if (usrlib->windowh->genWindow() == -1) {
        std::cout << "window generate error\n";
    }
    // shader generate
    shader tst("./renderer_glsl/test_vertex.glsl", "./renderer_glsl/test_frag.glsl");
    tst.enable();


	//std::cout << 1;
    delete usrlib;
    usrlib = nullptr;
	return 0;
}