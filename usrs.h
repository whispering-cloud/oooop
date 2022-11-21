#ifndef __USRS__
#define __USRS__
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>
#include <vector>
#include <irrKlang.h>
#include "include/ctrl/keyput.h"
#include "include/render/window.h"
#include "include/render/widget.h"
#include "include/render/shader.h"
#include "resources.h"

#pragma comment(lib, "irrKlang.lib")
#define re int
#define PROBE std::cout<<"probe"<<std::endl


const int MAX_WIDTH = 1920;
const int MAX_HEIGHT = 1080;

#define FRAMEBUFFER_ENABLE true


class usrs {
public:
	int tickrate;
	~usrs();
	void usrlib_init(void);
	void ticking(void);
	window* windowh;
	keyput* keyputh;
	std::vector<shader> glslPrograms;
	irrklang::ISoundEngine* soundEngine;
	GLFWwindow* wds;	// main window
	unsigned int fbo; // frame buffer object
	unsigned int rbo; // render buffer object
	unsigned int frameTexture;
	glm::highp_mat4 proj = glm::perspective(glm::radians(45.0f), float(MAX_WIDTH) / MAX_HEIGHT, 0.1f, 100.0f);
private:
	int tick_counter;
};

extern usrs* usrlib;
extern unsigned int rectIndices[6];
extern void logPrint(std::string logText);
extern void logError(int errid);

#endif // !__USRS__



