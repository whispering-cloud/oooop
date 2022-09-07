#ifndef __USRS__
#define __USRS__
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "include/ctrl/keyput.h"
#include "include/render/window.h"
#include "include/render/widget.h"
#include "include/render/shader.h"

class usrs {
public:
	~usrs();
	void usrlib_init(void);
	void ticking(void);

	window* windowh;
	keyput *keyputh;

	int keytable[127];
	GLFWwindow* wds;	// main window

private:
	int tick_counter;
};


#endif // !__USRS__

extern usrs* usrlib;


