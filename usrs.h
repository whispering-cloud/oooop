#ifndef __USRS__
#define __USRS__
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include "include/ctrl/keyput.h"
#include "include/render/window.h"
#include "include/render/widget.h"
#include "include/render/shader.h"
#define re int
const int MAX_HEIGHT = 800;
const int MAX_WIDTH = 1296;


class usrs {
public:
	int tickrate;
	~usrs();
	void usrlib_init(void);
	void ticking(void);
	void logPrint(std::string logText);
	window* windowh;
	keyput* keyputh;
	std::vector<shader> glslPrograms;

	GLFWwindow* wds;	// main window

private:
	int tick_counter;
};

extern usrs* usrlib;



#endif // !__USRS__



