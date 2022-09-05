#pragma once
#ifndef __USRS__
#define __USRS__
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "include/ctrl/keyput.h"
#include "include/render/window.h"

class usrs {
public:
	void usrlib_init(void);
	
	window* windowh;
	keyput* keyputh;

	int keytable[127];
	GLFWwindow* wds;	// main window

};


#endif // !__USRS__

extern usrs* usrlib;


